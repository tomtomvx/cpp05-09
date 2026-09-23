#include <iostream>
#include "Serializer.hpp"

int main(void)
{
	Data		data;
	Data*		restored;
	uintptr_t	raw;

	data.number = 42;
	data.message = "Serialization succeeded";
	raw = Serializer::serialize(&data);
	restored = Serializer::deserialize(raw);

	std::cout << "original:     " << &data << std::endl;
	std::cout << "serialized:   " << raw << std::endl;
	std::cout << "deserialized: " << restored << std::endl;
	if (restored != &data)
	{
		std::cerr << "Error: pointer mismatch" << std::endl;
		return (1);
	}
	std::cout << "number:       " << restored->number << std::endl;
	std::cout << "message:      " << restored->message << std::endl;
	std::cout << "Pointer round-trip: OK" << std::endl;
	return (0);
}
