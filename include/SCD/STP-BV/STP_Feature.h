



#ifndef _STP_FEATURE
#define _STP_FEATURE

#pragma once


#include <SCD/scd_api.h>
#include <SCD/Matrix/SCD_Types.h>
#include <vector>
#include <cstdlib>
namespace SCD
{
	typedef struct s_STP_VVR
	{
		s_STP_VVR();
		s_STP_VVR(Scalar cosangle, const Vector3& axis);
		s_STP_VVR(const s_STP_VVR& vvr);

		bool isInside(const Vector3& v) const;

		Scalar isInsidePrime(const Vector3& v) const;

		Scalar isInsidePlane(const Vector3& v) const;


		Scalar getDistance(const Vector3& v) const;

		bool isSameLimit(const s_STP_VVR& vvr) const;

		s_STP_VVR& operator=(const s_STP_VVR& vvr);
		bool operator==(const s_STP_VVR& vvr) const;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
      ar & m_axis & m_cosangle & m_outerSTP & m_displayList;
    }

		Vector3 m_axis;
		Scalar m_cosangle;
		int m_outerSTP;
		int m_displayList;
	} STP_VVR;


	/*! \struct s_STN_STBVData
	*  \brief
	*  \author Cochet-Grasset Amelie
	*  \date    october 2007
	*
	*  
	*/
	typedef struct s_STN_VVR
	{
		s_STN_VVR();
		s_STN_VVR(Scalar cosangle, const Vector3& axis);
		s_STN_VVR(const s_STN_VVR& vvr);

		bool isInside(const Vector3& v) const;
		Scalar getDistance(const Vector3& v) const;

		bool isSameLimit(const s_STN_VVR& vvr) const;

		s_STN_VVR& operator=(const s_STN_VVR& vvr);
		bool operator==(const s_STN_VVR& vvr) const;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
      ar & m_axis & m_cosangle & m_outerSTP & m_displayList;
    }

		Vector3 m_axis;
		Scalar m_cosangle;
		int m_outerSTP;
		int m_displayList;
	} STN_VVR;


	/*! \struct s_STP_STBVData
	*  \brief
	*  \author Cochet-Grasset Amelie
	*  \date    august 2007
	*
	*  
	*/
	typedef struct s_STP_STBVData
	{
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
      ar & m_points & m_VVRlimits & m_reverse & m_BVID;
    }

		std::vector<Point3> m_points;
		std::vector<STN_VVR> m_VVRlimits;
		std::vector<bool> m_reverse;
		int m_BVID;
	} STP_STBVData;



	enum STP_Featuretype
	{
		SMALLSPHERE,
		BIGSPHERE,
		TORUS
	};


	class STP_Feature
	{
	public:

		SCD_API virtual ~STP_Feature(void);

		SCD_API void setDisplayList(int l) {m_displayList = l;}

		SCD_API virtual void print() const = 0;
    #ifdef WITH_OPENGL
		SCD_API virtual void GLdisplay() const;
		SCD_API virtual void GLdisplayVVR() const = 0;
    #endif

		SCD_API virtual STP_Feature* clone() const =0;

		SCD_API virtual Point3 support(const Vector3& v) const=0;

		SCD_API virtual bool isHere(const Vector3& v) const = 0;
		SCD_API virtual bool isHereFarthestNeighbour(const Vector3& v) = 0;
		SCD_API virtual bool isHereFarthestNeighbourPrime(const Vector3& v) = 0;
		SCD_API virtual bool isHereFirstNeighbour(const Vector3& v) = 0;
		SCD_API virtual bool isHereFirstNeighbourPrime(const Vector3& v,int idp) = 0;
		SCD_API virtual bool isHereHybrid(const Vector3& v,int idp) = 0;
		SCD_API virtual int getNextBV(unsigned int id) const= 0;
		SCD_API virtual int getNextBVPrime() const=0 ;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
      ar & m_displayList & m_nextBVPrime;
    }

	protected:
		STP_Feature(void);

	protected:
		int m_displayList;
		int m_nextBVPrime;


	};

#include <SCD/STP-BV/STP_Feature.hxx>
}
#endif
