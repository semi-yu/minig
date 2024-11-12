#include <string>

namespace minig::auxil {
    class BaseException : public std::exception {
        std::string message_; 
    public:
        BaseException(std::string msg): message_(msg) {}

        const char* what() const noexcept override {
            return message_.c_str();
        }
    }; 

    class GlfwInitFailure : public BaseException{
    public:
        GlfwInitFailure(): BaseException("GLFW could not be initialized.") {}
    }; 

    class GladInitFailure : public BaseException {
    public:
        GladInitFailure() : BaseException("GLAD could not be initialized.") {}
    };
}