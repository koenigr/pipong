#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "math.h"

#include <cinttypes>
#include <cstring>
#include <atomic>
#include <thread>

#include <mraa.h>

#include <chrono>

#include "OLEDDisplay.h"



using namespace GFX;

OLEDDisplay disp(128, 128);
int X_MIN = 0;
int X_MAX = 127;
int Y_MIN = 0;
int Y_MAX = 127;
int L_WIDTH = 50;
int B_RAD = 10;

float TRESHHOLD = 0.1;
int move = 0;

// SENSORS
#define US_OFF  1
#define US_ON   0
#define US_LOW  1
#define US_HIGH 0

mraa_gpio_context us_trig;
mraa_gpio_context us_echo;
std::atomic<double> us_dist;


#define ADDR_MPU 0x68
#define ADDR_BME 0x77

#define MPU_SMPLRT_DIV     0x19
#define MPU_CONFIG         0x1A
#define MPU_GYRO_CONFIG    0x1B
#define MPU_ACCEL_CONFIG   0x1C
#define MPU_ACCEL_CONFIG_2 0x1D
#define MPU_INT_PIN_CFG    0x37
#define MPU_ACCEL_OUT      0x3B
// #define MPU_TEMP_OUT	   0x41
#define MPU_GYRO_OUT       0x43
#define MPU_PWR_MGMT_1     0x6B
#define MPU_PWR_MGMT_2     0x6C


#define BT_ON "X"
#define BT_OFF "O"

#define BME280_REGISTER_CONTROL_HUM 0xF2
#define BME280_REGISTER_CONTROL     0xF4
#define BME280_REGISTER_CONFIG      0xF5
#define BME280_REGISTER_DATA        0xF7

#define BME280_REGISTER_DIG_T1      0x88


int32_t dig_T1;
int32_t dig_T2;
int32_t dig_T3;


void debug(const char *txt, mraa_result_t r) {
	printf("%s: %d\n", txt, r);
}
void debug(const char *txt, void *r) {
	printf("%s: %p\n", txt, r);
}

double getTime() {
	struct timespec s;
	clock_gettime(CLOCK_MONOTONIC_RAW, &s);
	return s.tv_sec + s.tv_nsec * 1.0e-9;
}

void gpio_dir(mraa_gpio_context g, mraa_gpio_dir_t dir) {
	while (1) {
		mraa_result_t r = mraa_gpio_dir(g, dir);
		if (r == MRAA_SUCCESS)
			break;
		usleep(100 * 1000);
	}
}
mraa_gpio_context gpio_init(int pin, mraa_gpio_dir_t dir) {
	mraa_gpio_context c = mraa_gpio_init(pin);
	gpio_dir(c, dir);
	return c;
}

void runUS() {
	us_dist.store(0.0 / 0.0);
	mraa_gpio_write(us_trig, US_OFF);

	while (1) {
		usleep(100 * 1000);

		mraa_gpio_write(us_trig, US_ON);
		usleep(10);
		mraa_gpio_write(us_trig, US_OFF);

		while (mraa_gpio_read(us_echo) == US_LOW) ;
		double start = getTime();
		while (mraa_gpio_read(us_echo) == US_HIGH) ;
		double stop = getTime();

		double dist = (stop - start) * 17150;
		us_dist.store(dist);
	}
}


void initMPU9250(mraa_i2c_context i2c) {
	uint8_t gfs = 0; // 250.0° per 32768.0
	uint8_t afs = 0; // 2.0g per 32768.0

	// reset
	mraa_i2c_write_byte_data(i2c, 0x80, MPU_PWR_MGMT_1);
	usleep(100 * 1000);
	// sleep off
	mraa_i2c_write_byte_data(i2c, 0x00, MPU_PWR_MGMT_1);
	usleep(100 * 1000);
	// auto select clock source, sleep off
	mraa_i2c_write_byte_data(i2c, 0x01, MPU_PWR_MGMT_1);
	usleep(100 * 1000);
	// DLPF_CFG
	mraa_i2c_write_byte_data(i2c, 0x03, MPU_CONFIG);
	// sample rate divider
	mraa_i2c_write_byte_data(i2c, 0x04, MPU_SMPLRT_DIV);
	// gyro full scale select
	mraa_i2c_write_byte_data(i2c, gfs << 3, MPU_GYRO_CONFIG);
	// accel full scale select
	mraa_i2c_write_byte_data(i2c, afs << 3, MPU_ACCEL_CONFIG);
	// A_DLPFCFG
	mraa_i2c_write_byte_data(i2c, 0x03, MPU_ACCEL_CONFIG_2);
	// BYPASS_EN
	mraa_i2c_write_byte_data(i2c, 0x02, MPU_INT_PIN_CFG);
	usleep(100 * 1000);
}

static inline int16_t decodeS16BE(uint8_t *buf) {
	return (buf[0] << 8) | buf[1];
}
static inline uint16_t decodeU16BE(uint8_t *buf) {
	return (buf[0] << 8) | buf[1];
}
static inline int16_t decodeS16LE(uint8_t *buf) {
	return (buf[1] << 8) | buf[0];
}
static inline uint16_t decodeU16LE(uint8_t *buf) {
	return (buf[1] << 8) | buf[0];
}

void getAccel(mraa_i2c_context i2c, double *data) {
	uint8_t buf[2];
	memset(buf, 0, sizeof(buf));
	mraa_i2c_read_bytes_data(i2c, MPU_ACCEL_OUT, buf, 2);
	double f = 2.0 / 32768.0;
	data[0] = decodeS16BE(buf + 0) * f;

//	printf("%f\n", data[0]);
//	printf("%f\n", TRESHHOLD);

	if (data[0] > TRESHHOLD) {
		move = -1;
//		printf("move left\n");
	}
	else if (data[0] < -TRESHHOLD) {
		move = 1;
//		printf("move right\n");
	}
	else {
		move = 0;
		printf("NO MOVE");
	}

}

void initBME280(mraa_i2c_context i2c) {
	uint8_t standby = 3; //BME280_STANDBY_250
	uint8_t filter = 0;  //BME280_FILTER_off
	uint8_t h_mode = 1;  //BME280_OSAMPLE_1
	uint8_t t_mode = 1;  //BME280_OSAMPLE_1
	uint8_t p_mode = 1;  //BME280_OSAMPLE_1

	mraa_i2c_write_byte_data(i2c, 0x24, BME280_REGISTER_CONTROL);  // Sleep mode
	usleep(2 * 1000);
	mraa_i2c_write_byte_data(i2c, ((standby << 5) | (filter << 2)),
	BME280_REGISTER_CONFIG);
	usleep(2 * 1000);
	mraa_i2c_write_byte_data(i2c, h_mode, BME280_REGISTER_CONTROL_HUM); // Set Humidity Oversample
	mraa_i2c_write_byte_data(i2c, ((t_mode << 5) | (p_mode << 2) | 3),
	BME280_REGISTER_CONTROL); // Set Temp/Pressure Oversample and enter Normal mode

	uint8_t buf[6];
	memset(buf, 0, sizeof(buf));
	mraa_i2c_read_bytes_data(i2c, BME280_REGISTER_DIG_T1, buf, 6);
	dig_T1 = decodeU16LE(buf+0);
	dig_T2 = decodeS16LE(buf+2);
	dig_T3 = decodeS16LE(buf+4);
}

// SENSORS

void init() {

	disp.setBgColor(COLOR_BLACK);
	disp.setDrawColor(COLOR_WHITE);
	disp.clearScreen();
	disp.enable();

}



void draw() {
	disp.flush();
//	std::this_thread::sleep_for(std::chrono::seconds(1));
}

struct ball_pos {

	int posX = 0;
	int posY = 0;
	int velX = 4;
	int velY = 6;
} b_pos;

//struct ball_pos b_pos;

void compute_ball_pos() {

	if ( (b_pos.posX < X_MIN + B_RAD && b_pos.velX < 0) || (b_pos.posX > X_MAX - B_RAD && b_pos.velX > 0) ) {
		b_pos.velX = -b_pos.velX;
	}

	if ( (b_pos.posY < Y_MIN + B_RAD && b_pos.velY < 0) || (b_pos.posY > Y_MAX - B_RAD && b_pos.velY > 0)) {
		b_pos.velY = -b_pos.velY;
	}

	b_pos.posX += b_pos.velX;
	b_pos.posY += b_pos.velY;

}


void ball(int posX, int posY) {

        disp.fillCircle(posX, posY, B_RAD);
}

void line_p1(int pos) {

        disp.drawLine(X_MIN, pos - L_WIDTH / 2, X_MIN, pos + L_WIDTH / 2);

}

void line_p2(int pos) {

        disp.drawLine(pos - L_WIDTH / 2, Y_MIN, pos + L_WIDTH / 2, Y_MIN);

}

void line_p3(int pos) {

        disp.drawLine(X_MAX, pos - L_WIDTH / 2, X_MAX, pos + L_WIDTH / 2);

}

void line_p4(int pos) {

        disp.drawLine(pos - L_WIDTH / 2, Y_MAX, pos + L_WIDTH / 2, Y_MAX);

}


int main(void) {

	// SENSORS

	mraa_gpio_context led1 = gpio_init(33, MRAA_GPIO_OUT);
	mraa_gpio_context led2 = gpio_init(35, MRAA_GPIO_OUT);
	mraa_gpio_context led3 = gpio_init(37, MRAA_GPIO_OUT);

	mraa_gpio_write(led1, 1);
	mraa_gpio_write(led2, 1);
	mraa_gpio_write(led3, 1);

	us_trig = gpio_init(12, MRAA_GPIO_OUT);
	us_echo = gpio_init(18, MRAA_GPIO_IN);

	mraa_gpio_context bt_up = gpio_init(36, MRAA_GPIO_IN);
	mraa_gpio_context bt_lt = gpio_init(32, MRAA_GPIO_IN);
	mraa_gpio_context bt_ct = gpio_init(38, MRAA_GPIO_IN);
	mraa_gpio_context bt_rt = gpio_init(40, MRAA_GPIO_IN);
	mraa_gpio_context bt_dn = gpio_init(31, MRAA_GPIO_IN);

	mraa_i2c_context i2c = mraa_i2c_init(0);
	mraa_i2c_address(i2c, ADDR_MPU);
	initMPU9250(i2c);
	mraa_i2c_address(i2c, ADDR_BME);
	initBME280(i2c);

	char buf[1024];

	std::thread t_us(runUS);

	int up, lt, ct, rt, dn;
	double accel[3];

	// SENSORS


	init();
	printf("Starting\n");

	int i = 0;

	int player_pos = 60;

    while(true) {

    	int mv = sin(i)*20;
    	compute_ball_pos();

    	disp.clearScreen();
	disp.setCursor(0, 0);

	ball(b_pos.posX, b_pos.posY);


	player_pos += move*3;
	line_p4(player_pos);
    	line_p1(60 + mv);
    	line_p2(60 + mv);
    	line_p3(60 + mv);

    	// SENSORS

		up = !mraa_gpio_read(bt_up);
		lt = !mraa_gpio_read(bt_lt);
		ct = !mraa_gpio_read(bt_ct);
		rt = !mraa_gpio_read(bt_rt);
		dn = !mraa_gpio_read(bt_dn);

		mraa_gpio_write(led1, up || lt);
		mraa_gpio_write(led2, ct);
		mraa_gpio_write(led3, dn || rt);

		mraa_i2c_address(i2c, ADDR_MPU);
		getAccel(i2c, accel);

		mraa_i2c_address(i2c, ADDR_BME);

		sprintf(buf, "\n"
				"            %s\n"
				"Buttons:  %s %s %s\n"
				"            %s\n"
				"\n"
				"US Dist:%7.2fcm\n"
				"\n"
				"Accel  X:%7.2fg\n"
				, up ? BT_ON : BT_OFF, lt ? BT_ON : BT_OFF,
				ct ? BT_ON : BT_OFF, rt ? BT_ON : BT_OFF, dn ? BT_ON : BT_OFF,
				us_dist.load(), accel[0]);
		disp.print(buf);
    	// SENSORS


		draw();
		usleep(100000);
		i += 1;
    }

	return 0;
}
