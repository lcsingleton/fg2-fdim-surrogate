#ifndef CORE_CAN_H
#define CORE_CAN_H

namespace Core
{
namespace Can
{

enum SendResult
{
	SEND_FAILED,
	SEND_SUCCESS_QUEUE_1,
	SEND_SUCCESS_QUEUE_2,
	SEND_SUCCESS_QUEUE_3,
};

struct MsCanMessage
{
	unsigned int arbitrationId;
	unsigned char data;
};

SendResult SendPayload( const unsigned int arbitrationId, const unsigned char data[ 8 ] );

template<typename CanMessage>
SendResult Send( const CanMessage message )
{
	return SendPayload( message.arbitrationId, message.data );
}

void InitCanSystem();


} // namespace Can
} // namespace Core

#endif // CORE_CAN_H
