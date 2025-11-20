#pragma once
#include <unordered_map>
#include <string>
#include <functional>
#include <memory>
#include "Module.h"

class ModuleFactory {
public:
    using CreateFunc = std::function<std::shared_ptr<Module>()>;

    static ModuleFactory& Instance() {
        static ModuleFactory inst;
        return inst;
    }

    // 注册模块类型
    void RegisterType(const std::string& type, CreateFunc func) {
        creators[type] = func;
    }

    // 创建模块实例
    std::shared_ptr<Module> Create(const std::string& type) {
        auto it = creators.find(type);
        if (it != creators.end())
            return it->second();
        return nullptr;
    }

private:
    std::unordered_map<std::string, CreateFunc> creators;
};
