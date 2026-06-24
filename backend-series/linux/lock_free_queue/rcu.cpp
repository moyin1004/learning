
#include <atomic>
#include <iostream>
#include <vector>

using namespace std;

template <typename Config>
class ServerConfigManager {
public:
    virtual ~ServerConfigManager() {
        std::for_each(old_server_config_.begin(), old_server_config_.end(),
                      [](Config*& config) { delete config; });
        delete server_config_;
    }

    static ServerConfigManager& Instance() {
        static ServerConfigManager server_config_manager;
        return server_config_manager;
    }

    virtual std::string class_name() const { return typeid(Config).name(); };

    // 获取当前服务配置
    Config* GetServerConfig() {
        Config* config = server_config_.load(std::memory_order_acquire);
        return config;
    }

    virtual Config* NewConfig() { return new Config(); }

    virtual bool reset_value() {
        Config* config = NewConfig();
        // do some read config
        Config* old_config = server_config_.exchange(config, std::memory_order_acq_rel);
        if (old_config != nullptr) /* Already inited. */ {
            old_server_config_.push_back(old_config);
        }

        return true;
    }

private:
    std::atomic<Config*> server_config_{nullptr};
    std::vector<Config*> old_server_config_;
    std::vector<std::string> file_names_;
};