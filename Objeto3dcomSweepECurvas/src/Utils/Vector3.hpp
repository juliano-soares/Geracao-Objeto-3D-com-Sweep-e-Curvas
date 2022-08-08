/**
    Vector2 functions
    @file Vector3.h
    @author Juliano Leonardo Soares
    @version 1.1 03/05/22
*/

#ifndef __VECTOR_3_H__
#define __VECTOR_3_H__

class Vector3
{
public:
	float x, y, z;

	Vector3( void )
	{
		x = y = z = 0.0;
	};

	Vector3( const float tx, const float ty, const float tz )
	{
		x = tx;
		y = ty;
		z = tz;
	};

//	construtor de copia
	Vector3( const Vector3& v )
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
	};

    void setValor( const float tx, const float ty, const float tz )
	{
		x = tx;
		y = ty;
		z = tz;
	};

    //inicializacao de vetor
	void setValor(const Vector3 v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	};

//	Soma de vetores
	inline Vector3 operator + ( const Vector3 v )
	{
		Vector3 aux( x + v.x, y + v.y, z + v.z );
		return( aux );
	}

//	Subtracao de vetores
	inline Vector3 operator - ( const Vector3 v )
	{
		Vector3 aux( x - v.x, y - v.y, z - v.z );
		return( aux );
	}

//	Produto por escalar (float)
	inline Vector3 operator * ( const float s )
	{
		Vector3 aux( x * s, y * s, z * s );
		return( aux );
	}

//	Divisao por escalar
	inline Vector3  operator / ( const float s )
	{
		Vector3 aux( x / s, y / s, z / s );
		return( aux );
	}

//	Produto escalar
	inline float operator * ( const Vector3 v )
	{
		float aux = x * v.x + y * v.y + z * v.z;
		return( aux );
	}

//	Produto vetorial
	inline Vector3 operator ^ ( Vector3 v )
	{
		Vector3 aux( y * v.z - z * v.y,
			       z * v.x - x * v.z,
			       x * v.y - y * v.x );
		return( aux );
	}

//  norma do vetor
	float norma( void )
	{
		return (float)( sqrt( x * x + y * y + z * z ) );
	}

	float distancia( Vector3 v )
	{
		return( (*this - v).norma() );
	}

//	normaliza o vetor
	Vector3 normalize( void )
	{
		return( (*this) / (this->norma()) );
	}

	//	normaliza o vetor
	Vector3 extende(float val)
	{
		return ((*this) * (val) );
	}
};

#endif
