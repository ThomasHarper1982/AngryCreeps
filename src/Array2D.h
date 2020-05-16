#ifndef ARRAY2D_H
#define ARRAY2D_H

#include <vector>
#include <algorithm>
#include <cassert>

/**
 * class Array2D - Implementation of an 2D Array
 **/

template<typename T>
class Array2D
{
public:
	Array2D(size_t rows, size_t cols): m_RowCount(rows), m_ColCount(cols)
	{
	//assert(rows > 0 && cols > 0);
		m_Items.resize(rows * cols);
		std::fill(m_Items.begin(), m_Items.end(), T());
	}
	Array2D(size_t rows, size_t cols, const T& val) : m_RowCount(rows), m_ColCount(cols)
	{
		//assert(rows > 0 && cols > 0);
		m_Items = new T[rows * cols];
		std::fill(m_Items.begin(), m_Items.end(), val);
	}

	void clear(){
		m_Items.clear();
	}

	size_t rows() const 
	{ 
		return m_RowCount; 
	}
	
	size_t cols() const 
	{ 
		return m_ColCount; 
	}

	T& operator()(const size_t row, const size_t col)
	{
		//std::cout << "op:start" << std::endl;
		//assert(row > 0 && col > 0);
		size_t index = row * m_ColCount + col;
		//std::cout << "op:end" << std::endl;
		return m_Items[index];
	}
	
	const T& operator()(const size_t row, const size_t col) const
	{
		//assert(row > 0 && col > 0);
		size_t index = row * m_ColCount + col;

		return m_Items[index];
	}

	T* operator[](size_t row)
	{
		//assert(row < m_RowCount);
		return &m_Items[row * m_ColCount];
	}

	const T* operator[](size_t row) const
	{
		//assert(row < m_RowCount);

		return &m_Items[row * m_ColCount];
	}

	
private:
	std::vector<T> m_Items;
	size_t  m_RowCount, m_ColCount;
};
#endif