#ifndef DETECTIONMAP_H
#define DETECTIONMAP_H

#include <vector>
#include <algorithm>
#include <cassert>
#include "Agent.h"
#include <iostream>
//#include <memory>

/**
 * class Array2D - Implementation of an 2D Array
 **/

class TileBin{

	public:
		TileBin();//bin = new std::vector<Agent*> ();}

		std::vector<Agent*>* getTileBin(){return bin;	}
		static const int count = 0;
		int id;
	private:
		std::vector<Agent*> *bin;
};

class DetectionMap
{
public:
	DetectionMap(){};

	DetectionMap(int rows, int cols): m_RowCount(rows), m_ColCount(cols)
	{
		//std::cout << "Detection Map: start" <<std::endl;
		//assert(rows > 0 && cols > 0);
		//m_Items.resize(rows * cols);
		//std::cout<<m_Items.size() << std::endl;
		//std::fill(m_Items.begin(), m_Items.end(),  TileBin());
		for (int i = 0; i < rows*cols; i++){
			m_Items.push_back(TileBin());
        }
		std::cout<<m_Items.size() << std::endl;
	}

	void clearMap(){
		for (TileBin t : m_Items){
			t.getTileBin()->clear();
		}
		//m_Items.clear();
	}
/**	DetectionMap(size_t rows, size_t cols, const T& val) : m_RowCount(rows), m_ColCount(cols)
	{
		assert(rows > 0 && cols > 0);
		m_Items = new T[rows * cols];
		std::fill(m_Items.begin(), m_Items.end(), val);
	}**/

	size_t rows() const 
	{ 
		return m_RowCount; 
	}
	
	size_t cols() const 
	{ 
		return m_ColCount; 
	}

	TileBin operator()(const size_t row, const size_t col)
	{
	//	assert(row > 0 && col > 0);
		size_t index = row * m_ColCount + col;
		
		return m_Items[index];
	}
	
	const TileBin operator()(const size_t row, const size_t col) const
	{
		//assert(row > 0 && col > 0);
		size_t index = row * m_ColCount + col;

		return m_Items[index];
	}

	
private:

	std::vector<TileBin> m_Items;
	size_t  m_RowCount, m_ColCount;
};
#endif