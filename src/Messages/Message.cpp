#include "Sennet/Messages/Message.hpp"

namespace Sennet
{

Ref<MessageEncoding> MessageEncoder::Encode(const Ref<Message>& msg)
{
	namespace serializer = zpp::serializer;
	auto data = CreateRef<MessageEncoding>();
	serializer::memory_output_archive out(*data);
	
	try
	{
		out(msg);	
	}
	catch (const serializer::out_of_range& e)
	{
		SN_CORE_WARN("[Encoder] Encoding exception: {0}", e.what());
		return nullptr;
	}
	catch (const serializer::undeclared_polymorphic_type_error& e)
	{
		SN_CORE_WARN("[Encoder] Encoding exception: {0}", e.what());
		return nullptr;
	}
	catch (const serializer::attempt_to_serialize_null_pointer_error& e)
	{
		SN_CORE_WARN("[Encoder] Encoding exception: {0}", e.what());
		return nullptr;
	}
	catch (const serializer::polymorphic_type_mismatch_error& e)
	{
		SN_CORE_WARN("[Encoder] Encoding exception: {0}", e.what());
		return nullptr;
	}
	catch (const serializer::attempt_to_serialize_valueless_variant& e)
	{
		SN_CORE_WARN("[Encoder] Encoding exception: {0}", e.what());
		return nullptr;
	}
	catch (const serializer::variant_index_out_of_range& e)
	{
		SN_CORE_WARN("[Encoder] Encoding exception: {0}", e.what());
		return nullptr;
	}

	return data;
}

Ref<Message> MessageEncoder::Decode(const Ref<MessageEncoding>& rawMsg)
{
	namespace serializer = zpp::serializer;
	Ref<Message> msg = nullptr;
	serializer::memory_input_archive in(*rawMsg);
	
	try
	{
		in(msg);
	}
	catch (const serializer::out_of_range& e)
	{
		SN_CORE_WARN("[Encoder] Decoding exception: {0}", e.what());
		return nullptr;
	}
	catch (const serializer::undeclared_polymorphic_type_error& e)
	{
		SN_CORE_WARN("[Encoder] Decoding exception: {0}", e.what());
		return nullptr;
	}
	catch (const serializer::attempt_to_serialize_null_pointer_error& e)
	{
		SN_CORE_WARN("[Encoder] Decoding exception: {0}", e.what());
		return nullptr;
	}
	catch (const serializer::polymorphic_type_mismatch_error& e)
	{
		SN_CORE_WARN("[Encoder] Decoding exception: {0}", e.what());
		return nullptr;
	}
	catch (const serializer::attempt_to_serialize_valueless_variant& e)
	{
		SN_CORE_WARN("[Encoder] Decoding exception: {0}", e.what());
		return nullptr;
	}
	catch (const serializer::variant_index_out_of_range& e)
	{
		SN_CORE_WARN("[Encoder] Decoding exception: {0}", e.what());
		return nullptr;
	}

	return msg;
}

}
