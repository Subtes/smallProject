#ifndef ATP_MODEL_H
#define ATP_MODEL_H

#include <string>
#include <QObject>

class ATP_model
{

private:
    double m_allowedSpeed;
    double m_targetSpeed;
    std::string m_code;
    bool m_traction;

public:
    ATP_model();
    ~ATP_model();
    bool tractionReady();
    void reset();

    double allowedSpeed() const;
    void setAllowedSpeed(double allowedSpeed);
    double targetSpeed() const;
    void setTargetSpeed(double targetSpeed);
    std::string code() const;
    void setCode(const std::string &code);

    void cutTraction();
    void enableTraction();
};

#endif // ATP_MODEL_H
