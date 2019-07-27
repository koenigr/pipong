#include "../../gamestate/GameState.h"
#include "../../message_protocol/MessageProtocol.h"

#include <string>

int main(int argc, int agv[]) {

    GameState gs0;
    gs0.init(0);
    std::string req0;

    GameState gs1;
    gs1.init(1);
    std::string req1;

    GameState gs2;
    gs2.init(2);
    std::string req2;

    while (gs0.getCountdown() > COUNTDOWN_START_VAL / 2) {

        req0 = MessageProtocol::createRequest(gs0);
        gs0.incrFrameNo();
        gs0.decrCountdown();

    }

    while (gs0.getCountdown() > COUNTDOWN_START_VAL / 2) {

        req0 = MessageProtocol::createRequest(gs0);
        gs0.incrFrameNo();
        gs0.decrCountdown();

        req1 = MessageProtocol::createRequest(gs1);
        gs1.incrFrameNo();
        gs1.decrCountdown();

        MessageProtocol::evalMessage(0, req0, gs1);
        MessageProtocol::evalMessage(0, req1, gs0);


    }

    while (gs0.getCountdown() > 0 && gs1.getCountdown() > 0) {

        req0 = MessageProtocol::createRequest(gs0);
        gs0.incrFrameNo();
        gs0.decrCountdown();

        req1 = MessageProtocol::createRequest(gs1);
        gs1.incrFrameNo();
        gs1.decrCountdown();

        req2 = MessageProtocol::createRequest(gs2);
        gs2.incrFrameNo();
        gs2.decrCountdown();

        MessageProtocol::evalMessage(0, req1, gs0);
        MessageProtocol::evalMessage(0, req2, gs0);

        MessageProtocol::evalMessage(0, req0, gs1);
        MessageProtocol::evalMessage(0, req2, gs1);

        MessageProtocol::evalMessage(0, req0, gs2);
        MessageProtocol::evalMessage(0, req1, gs2);

    }

}
