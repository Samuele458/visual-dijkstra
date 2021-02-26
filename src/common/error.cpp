#include "error.h"

Error::Error( id error_id, QString message ) :
    message( message ), error_id( error_id )
{

}

Error::id Error::getId() const {
    return error_id;
}

void Error::setId( id error_id ) {
    this->error_id = error_id;
}

QString Error::getMessage() const {
    return message;
}

void Error::setMessage( QString message ) {
    this->message = message;
}
