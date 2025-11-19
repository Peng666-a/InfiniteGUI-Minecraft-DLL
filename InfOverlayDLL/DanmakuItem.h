#include "InfoItem.h"
#include <vector>
#include <string>
#include <deque>
#include <mutex>

enum bottonMessageType {
    BTM_ENTRY,
    BTM_GIFT,
    BTM_LIKE,
    BTM_CAPTAIN
};

typedef int danmaku_id;

struct Danmaku {
    std::string username;
    std::string message;
    danmaku_id id;
};

struct danmaku_element {
    ImVec4 color;
    float curHeight = 0;
    float tarHeight = 0;
};



class DanmakuItem : public InfoItem {
public:
    DanmakuItem()
    {
        windowTitle = "Bilibili Danmaku";
        refreshIntervalMs = 1000;   // 默认 1 秒刷一次
    }

    virtual ~DanmakuItem();

    // 更新弹幕内容
    void AddDanmaku(const std::string& username, const std::string& message);
    void AddCaptain(const std::string& username, const std::string& captainName, const std::string& captainCount);
    void AddGift(const std::string& username, const std::string& giftName, const std::string& giftCount);
    void AddUserEntry(const std::string& username);
    void AddUserLike(const std::string& username);


    void Update() override;
    void DrawContent() override;

    void Load(const nlohmann::json& j) override;
    void Save(nlohmann::json& j) const override;

protected:
    // 弹幕内容
    std::deque<Danmaku> danmakuList;

    std::string bottomMessage = "";
    bottonMessageType bottomMessageType = BTM_ENTRY;

    danmaku_id id = 0;
    std::map<danmaku_id, danmaku_element> anim;
    //std::mutex danmakuMutex;
    FILETIME lastWriteTime = {};
    bool isScrollable = false;

public:
    // 最大弹幕数量
    int maxDanmakuCount = 50;

    //弹幕日志位置
    std::string logPath = "lastrun.txt";



};