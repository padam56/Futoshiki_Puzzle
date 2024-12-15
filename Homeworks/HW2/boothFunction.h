#ifndef BOOTH_FUNC_H
#define BOOTH_FUNC_H

#include "typedef.h"
#include "twoVariableEnergyFunc.h"

class boothFunction : public twoVariableEnergyFunc
{
public:
    // Constructors and Destructor
    boothFunction();
    boothFunction(vector<PCReal> itsPosition);
    boothFunction(PCReal _x, PCReal _y);
    virtual ~boothFunction();

    // Accessors
    virtual PCReal evaluate();
    virtual PCReal evaluate() const;
    static PCReal evaluate(vector<PCReal> _pos);
    static PCReal evaluate(PCReal _x, PCReal _y);

private:
#ifdef HAS_BOOST_SERIALIZE
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<twoVariableEnergyFunc>(*this);
    }
#endif

protected:
};

#endif // BOOTH_FUNC_H