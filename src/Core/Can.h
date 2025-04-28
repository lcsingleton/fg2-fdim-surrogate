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
	uint32_t arbitrationId;
	uint8_t data;
}

SendResult SendPayload( uint32_t arbitrationId, const uint8_t data[ 8 ] );

template<MsCanMessage canMessage>
SendResult Send( const MsCanMessage message )
{
	return SendPayload( message.arbitrationId, message.data );
}

void InitCanSystem();

}
} // namespace Can
} // namespace Core

#endif // CORE_CAN_H
