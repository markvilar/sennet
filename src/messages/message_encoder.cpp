#include <sennet/messages/message_encoder.hpp>

namespace sennet
{

ref<message_encoding> message_encoder::encode(const ref<message>& msg)
{
	namespace serializer = zpp::serializer;
	auto data = create_ref<message_encoding>();
	serializer::memory_output_archive out(*data);
	
	try
	{
		out(msg);	
	}
	catch (const serializer::out_of_range& e)
	{
		SN_CORE_WARN("Encoding exception: {0}", e.what());
		return nullptr;
	}
	catch (const serializer::undeclared_polymorphic_type_error& e)
	{
		SN_CORE_WARN("Encoding exception: {0}", e.what());
		return nullptr;
	}
	catch (const serializer::attempt_to_serialize_null_pointer_error& e)
	{
		SN_CORE_WARN("Encoding exception: {0}", e.what());
		return nullptr;
	}
	catch (const serializer::polymorphic_type_mismatch_error& e)
	{
		SN_CORE_WARN("Encoding exception: {0}", e.what());
		return nullptr;
	}
	catch (const serializer::attempt_to_serialize_valueless_variant& e)
	{
		SN_CORE_WARN("Encoding exception: {0}", e.what());
		return nullptr;
	}
	catch (const serializer::variant_index_out_of_range& e)
	{
		SN_CORE_WARN("Encoding exception: {0}", e.what());
		return nullptr;
	}

	return data;
}

ref<message> message_encoder::decode(const ref<message_encoding>& raw_msg)
{
	namespace serializer = zpp::serializer;
	ref<message> msg = nullptr;
	serializer::memory_input_archive in(*raw_msg);
	
	try
	{
		in(msg);
	}
	catch (const serializer::out_of_range& e)
	{
		SN_CORE_WARN("Decoding exception: {0}", e.what());
		return nullptr;
	}
	catch (const serializer::undeclared_polymorphic_type_error& e)
	{
		SN_CORE_WARN("Decoding exception: {0}", e.what());
		return nullptr;
	}
	catch (const serializer::attempt_to_serialize_null_pointer_error& e)
	{
		SN_CORE_WARN("Decoding exception: {0}", e.what());
		return nullptr;
	}
	catch (const serializer::polymorphic_type_mismatch_error& e)
	{
		SN_CORE_WARN("Decoding exception: {0}", e.what());
		return nullptr;
	}
	catch (const serializer::attempt_to_serialize_valueless_variant& e)
	{
		SN_CORE_WARN("Decoding exception: {0}", e.what());
		return nullptr;
	}
	catch (const serializer::variant_index_out_of_range& e)
	{
		SN_CORE_WARN("Decoding exception: {0}", e.what());
		return nullptr;
	}

	/*
	out_of_range
	undeclared_polymorphic_type_error
	attempt_to_serialize_null_pointer_error
	polymorphic_type_mismatch_error
	attempt_to_serialize_valueless_variant
	variant_index_out_of_range
	*/

	return msg;
}

}
