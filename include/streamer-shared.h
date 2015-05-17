#ifndef STREAMER_SHARED_H
#define STREAMER_SHARED_H

#include <QFlags>
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
class StreamCmdFlags {
public:
    enum StreamCommands {
        Cmd_Null,
        ScreenDimensions,
        AvDescriptor
    };
    Q_DECLARE_FLAGS(Commands,StreamCommands)
};
Q_DECLARE_OPERATORS_FOR_FLAGS(StreamCmdFlags::Commands)

#endif //STREAMER_SHARED_H
