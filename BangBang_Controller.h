//#include "Controller.h"
//#include "LiveWindowSendable"
//#include "ITableListener"

class BangBang_Controller : public LiveWindowSendable, public Controller, public ITableListener
{
public:
	BangBang_Controller(PIDSource *source, PIDOutput *output);
	BangBang_Controller(float p, float i, float d, float f,
                    PIDSource *source, PIDOutput *output,
                    float period = 0.05);
    virtual ~BangBang_Controller();
    virtual float Get();
    virtual void SetContinuous(bool continuous = true);
    virtual void SetInputRange(float minimumInput, float maximumInput);
    virtual void SetOutputRange(float mimimumOutput, float maximumOutput);
    virtual void SetPID(float p, float i, float d);
    virtual void SetPID(float p, float i, float d, float f);
    virtual float GetP();
    virtual float GetI();
    virtual float GetD();
    virtual float GetF();

    virtual void SetSetpoint(float setpoint);
    virtual float GetSetpoint();

    virtual float GetError();

    virtual void SetTolerance(float percent);
    virtual void SetAbsoluteTolerance(float absValue);
    virtual void SetPercentTolerance(float percentValue);
    virtual bool OnTarget();

    virtual void Enable();
    virtual void Disable();
    virtual bool IsEnabled();

    virtual void Reset();

    virtual void InitTable(ITable* table);

private:
    float m_P;          // factor for "proportional" control
    float m_I;          // factor for "integral" control
    float m_D;          // factor for "derivative" control
    float m_F;          // factor for "feed forward" control
    float m_maximumOutput;  // |maximum output|
    float m_minimumOutput;  // |minimum output|
    float m_maximumInput;       // maximum input - limit setpoint to this
    float m_minimumInput;       // minimum input - limit setpoint to this
    bool m_continuous;  // do the endpoints wrap around? eg. Absolute encoder
    bool m_enabled;             //is the pid controller enabled
    float m_prevError;  // the prior sensor input (used to compute velocity)
    double m_totalError; //the sum of the errors for use in the integral calc
    enum {kAbsoluteTolerance, kPercentTolerance, kNoTolerance} m_toleranceType;
    float m_tolerance;  //the percetage or absolute error that is considered on target
    float m_setpoint;
    float m_error;
    float m_result;
    float m_period;

    SEM_ID m_semaphore;

    PIDSource *m_pidInput;
    PIDOutput *m_pidOutput;
    Notifier *m_controlLoop;

    void Initialize(PIDSource *source, PIDOutput *output);
    static void CallCalculate(void *controller);
    void Calculate();

    virtual ITable* GetTable();
    virtual std::string GetSmartDashboardType();
    virtual void ValueChanged(ITable* source, const std::string& key, EntryValue value, bool isNew);
    virtual void UpdateTable();
    virtual void StartLiveWindowMode();
    virtual void StopLiveWindowMode();
protected:
    ITable* m_table;

    DISALLOW_COPY_AND_ASSIGN(BangBang_Controller);
};
