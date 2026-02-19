#ifndef ERROR_HANDLER_HPP
#define ERROR_HANDLER_HPP

#define ERROR_CODE_LIST \
    X(FILE_OPEN_FAILED) \
    X(INVALID_FORMAT) \
    X(PARSE_ERROR) \
    X(UNKNOWN_ERROR)


enum struct ErrorCode {
    #define X(name) name,
    ERROR_CODE_LIST
    #undef X
};

inline const char* errorCodeToString(ErrorCode code) {
    switch(code) {
        #define X(name) case ErrorCode::name: return #name;
        ERROR_CODE_LIST
        #undef X
        default: return "UNRECOGNIZED_ERROR";
    }
}

#endif