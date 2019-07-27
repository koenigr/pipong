#include <iostream>

#include "../../network/AddressManager.h"

int main() {
    AddressManager am;
    am.init();

    std::cout << "Number of participants: " << am.getNumOfParticipants() << std::endl;

    am.addParticipant(0);

    std::cout << "Number of participants: " << am.getNumOfParticipants() << std::endl;
    for (int i = 0; i < am.getNumOfParticipants(); i++) {
        char str[INET_ADDRSTRLEN];
        sockaddr_in participant;
        am.getParticipant(i, participant);
        inet_ntop(AF_INET, &(participant.sin_addr), str, INET_ADDRSTRLEN);
        std::cout << "Participant: " << str << std::endl;
    }

    am.addParticipant(2);

    std::cout << "Number of participants: " << am.getNumOfParticipants() << std::endl;
    for (int i = 0; i < am.getNumOfParticipants(); i++) {
        char str[INET_ADDRSTRLEN];
        sockaddr_in participant;
        am.getParticipant(i, participant);
        inet_ntop(AF_INET, &(participant.sin_addr), str, INET_ADDRSTRLEN);
        std::cout << "Participant: " << str << std::endl;
    }

    am.addParticipant(1);

    std::cout << "Number of participants: " << am.getNumOfParticipants() << std::endl;
    for (int i = 0; i < am.getNumOfParticipants(); i++) {
        char str[INET_ADDRSTRLEN];
        sockaddr_in participant;
        am.getParticipant(i, participant);
        inet_ntop(AF_INET, &(participant.sin_addr), str, INET_ADDRSTRLEN);
        std::cout << "Participant: " << str << std::endl;
    }

    am.addParticipant(3);

    std::cout << "Number of participants: " << am.getNumOfParticipants() << std::endl;
    for (int i = 0; i < am.getNumOfParticipants(); i++) {
        char str[INET_ADDRSTRLEN];
        sockaddr_in participant;
        am.getParticipant(i, participant);
        inet_ntop(AF_INET, &(participant.sin_addr), str, INET_ADDRSTRLEN);
        std::cout << "Participant: " << str << std::endl;
    }

    am.addParticipant(4);

    std::cout << "Number of participants: " << am.getNumOfParticipants() << std::endl;
    for (int i = 0; i < am.getNumOfParticipants(); i++) {
        char str[INET_ADDRSTRLEN];
        sockaddr_in participant;
        am.getParticipant(i, participant);
        inet_ntop(AF_INET, &(participant.sin_addr), str, INET_ADDRSTRLEN);
        std::cout << "Participant: " << str << std::endl;
    }
}
