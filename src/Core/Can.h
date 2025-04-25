#ifndef CAN_H
#define CAN_H

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

SendResult SendPayload( uint32_t arbitrationId, const uint8_t data[ 8 ] );

template<typename Type>
SendResult Send( const Type message )
{
	return SendPayload( message.arbitationId, message.data );
}

void SetupCanComms();

}
} // namespace Can
} // namespace Core

#endif // CAN_H
