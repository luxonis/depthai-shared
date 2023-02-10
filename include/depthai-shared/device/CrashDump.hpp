#pragma once

// std
#include <cstdint>
#include <unordered_map>

// project
#include "depthai-shared/common/ProcessorType.hpp"
#include "depthai-shared/common/optional.hpp"
#include "depthai-shared/utility/Serialization.hpp"

namespace dai {

struct CrashDump {
    struct CrashReport {
        ProcessorType processor;
        std::string errorSource;

        struct ErrorSourceInfo {
            struct AssertContext {
                std::string fileName;
                std::string functionName;
                uint32_t line;
                DEPTHAI_SERIALIZE(AssertContext, fileName, functionName, line);
            };

            AssertContext assertContext;

            struct TrapContext {
                uint32_t trapNumber;
                uint32_t trapAddress;
                std::string trapName;
                DEPTHAI_SERIALIZE(TrapContext, trapNumber, trapAddress, trapName);
            };

            TrapContext trapContext;

            uint32_t errorId;

            DEPTHAI_SERIALIZE(ErrorSourceInfo, assertContext, trapContext, errorId);
        };

        ErrorSourceInfo errorSourceInfo;

        struct ThreadCallstack {
            uint32_t threadId;
            std::string threadName;
            uint32_t stackBottom;
            uint32_t stackTop;
            uint32_t stackPointer;
            uint32_t instructionPointer;
            std::string threadStatus;

            struct CallstackContext {
                uint32_t callSite;
                uint32_t calledTarget;
                uint32_t framePointer;
                std::string context;
                DEPTHAI_SERIALIZE(CallstackContext, callSite, calledTarget, framePointer, context);
            };

            std::vector<CallstackContext> callStack;

            DEPTHAI_SERIALIZE(ThreadCallstack, threadId, threadName, stackBottom, stackTop, stackPointer, instructionPointer, threadStatus, callStack);
        };

        std::vector<ThreadCallstack> threadCallstack;
        DEPTHAI_SERIALIZE(CrashReport, processor, errorSource, threadCallstack);
    };

    std::vector<CrashReport> crashReports;
};

DEPTHAI_SERIALIZE_EXT(CrashDump, crashReports);

}  // namespace dai
