#ifndef CORE_SERIAL_H
#define CORE_SERIAL_H

namespace Core
{
namespace Serial
{

enum SendResult
{
	SEND_FAILED,
	SEND_SUCCESS,
};


SendResult SendPayload( const unsigned int arbitrationId, const unsigned char data[ 8 ] );


void InitUsartSystem();


} // namespace Serial
} // namespace Core

#endif // CORE_SERIAL_H