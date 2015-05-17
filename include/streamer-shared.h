#ifndef STREAMER_SHARED_H
#define STREAMER_SHARED_H

namespace StreamerSharedProperties {
	enum StreamProtocol {
            SP_JsonTransmission,
            SP_BinaryTransmission
        };

        //We use an enum to avoid spamming the input stream with characters.
        //Instead, there are a ton of numbers.
        enum StreamDetailers {
            SD_InputSignal,
            SD_CommandSignal
        };
}

#endif //STREAMER_SHARED_H
