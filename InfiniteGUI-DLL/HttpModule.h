#pragma once
class HttpModule
{
public:
    //virtual void HttpAddTask() = 0;
    //virtual void HttpRemoveTask() = 0; 
    //void HttpResetTask()
    //{
    //    HttpRemoveTask();
    //    HttpAddTask();
    //}

    virtual void UpdateHttp() = 0;
protected:
    int httpUpdateIntervalMs = 100;
    //int httpTaskId;
};