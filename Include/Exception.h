#include <exception>

namespace ALang { namespace Error {

class OperationError : public std::exception
{
    std::string Msg;

public:
    OperationError( const char* Str ) : std::exception(), Msg( Str ) {}

    const char* what() const noexcept
    {
        return this->Msg.c_str();
    }
};

}} // Namespace ALang, Error
