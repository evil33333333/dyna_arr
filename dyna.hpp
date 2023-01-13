#include <cstdlib>
#include <cstring>

class dyna_arr
{
private:
	void* m_buf;
	size_t m_size;
	size_t m_position;
public:
	dyna_arr()
	{
		this->m_size = 0;
		this->m_position = 0;
	}

	dyna_arr(size_t size)
	{
		this->m_buf = malloc(size);
		this->m_size = size;
		this->m_position = 0;
	}

	~dyna_arr()
	{
		free(this->m_buf);
		this->m_size = 0;
		this->m_position = 0;
	}

	// returns the size
	const size_t size()
	{
		return this->m_size;
	}

	// resets the write position to zero
	void reset_position()
	{
		this->m_position = 0;
	}

	// set the write position to custom value, returns -1 if successful, else returns the current size
	const int set_position(size_t position)
	{
		if (position > this->m_size)
		{
			return this->m_size;
		}
		this->m_position = position;
		return -1;
	}

	// write to the array
	void write(void* memory, size_t len)
	{
		if (len + this->m_position > this->m_size)
		{
			this->m_buf = realloc(this->m_buf, this->m_size + len);
			this->m_size = this->m_size + len;
		}

		memcpy(reinterpret_cast<void*>((uintptr_t)this->m_buf + this->m_position), memory, len);
		this->m_position += len;
	}

	// read the memory from buffer
	const void* read()
	{
		return this->m_buf;
	}

	// reads byte at position without changing current position
	const int read_byte(size_t position)
	{
		return *(reinterpret_cast<unsigned char*>((uintptr_t)this->m_buf + position));
	}

	// reinterpret bytes as another type
	template <typename T>
	T reinterpret()
	{
		return *reinterpret_cast<T*>(this->m_buf);
	}
};
