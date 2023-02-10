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
            enum class ThreadStatus : uint32_t {
                READY = 0x00000000,
                WAITING_FOR_MUTEX = 0x00000001,
                WAITING_FOR_SEMAPHORE = 0x00000002,
                WAITING_FOR_EVENT = 0x00000004,
                WAITING_FOR_SYSTEM_EVENT = 0x00000008,
                WAITING_FOR_MESSAGE = 0x00000010,
                WAITING_FOR_CONDITION_VARIABLE = 0x00000020,
                WAITING_FOR_FUTEX = 0x00000040,
                WAITING_FOR_BSD_WAKEUP = 0x00000080,
                WAITING_FOR_TIME = 0x00000100,
                WAITING_FOR_PERIOD = 0x00000200,
                WAITING_FOR_SIGNAL = 0x00000400,
                WAITING_FOR_BARRIER = 0x00000800,
                WAITING_FOR_RWLOCK = 0x00001000,
                WAITING_FOR_JOIN_AT_EXIT = 0x00002000,
                WAITING_FOR_JOIN = 0x00004000,
                SUSPENDED = 0x00008000,
                WAITING_FOR_SEGMENT = 0x00010000,
                LIFE_IS_CHANGING = 0x00020000,
                DEBUGGER = 0x08000000,
                INTERRUPTIBLE_BY_SIGNAL = 0x10000000,
                WAITING_FOR_RPC_REPLY = 0x20000000,
                ZOMBIE = 0x40000000,
                DORMANT = 0x80000000,
                LOCALLY_BLOCKED = 0x00006CF3,
                BLOCKED = 0x30006FFF,
                ALL_SET = 0xFFFFFFFF
            };

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
