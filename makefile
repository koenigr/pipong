CC = g++
CPPFLAGS = -std=c++11 -lmraa -pthread -Wall -Wextra -Wpedantic 

STATES = states/StateManager.o
DISPLAY = display/Display.o
GAMESTATE = gamestate/GameState.o gamestate/Player.o gamestate/Ball.o
INPUT = input/InputManager.o
MESSAGE_PROTOCOL = message_protocol/MessageProtocol.o
MRAA_LIBS = mraa_libs/Canvas.o mraa_libs/OLEDDisplay.o mraa_libs/Print.o
NETWORK = network/UDPSocket.o network/AddressManager.o
TOOLS = tools/Tools.o

OBJS = pipong.o  $(STATES)  $(DISPLAY) $(GAMESTATE) $(INPUT) $(MESSAGE_PROTOCOL) $(MRAA_LIBS) $(NETWORK) $(TOOLS)

MAIN = PiPong


$(MAIN): $(OBJS) Parameters.h
	$(CC) -o $@ $^ $(CPPFLAGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CPPFLAGS)

clean:
	rm -f core $(MAIN) $(OBJS)
