#ifndef ERROR_H
#define ERROR_H
#include <QString>

class Error
{

public:
    enum id {
        GENERIC,
        INVALID_ARGUMENT,
    };

    Error( id error_id = GENERIC, QString message = "" );

    id getId() const;
    void setId( id error_id );
    QString getMessage() const;
    void setMessage( QString message );


private:
    QString message;
    id error_id;

};

#endif // ERROR_H
