#include <map>
#include <string>
#include <iostream>

class VeryHeavyDatabase {
public:
    std::string GetData(const std::string& key) const noexcept {
        return "Very Big Data String: " + key;
    }
};

class OneShotDB : public VeryHeavyDatabase {
private:
    VeryHeavyDatabase* real_object_;
    mutable size_t shots_left_;
public:
    explicit OneShotDB(VeryHeavyDatabase* real_object, size_t shots=1) : real_object_(real_object), shots_left_(shots) {}
    std::string GetData(const std::string& key) const noexcept {
        if (shots_left_ > 0) {
            --shots_left_;
            return real_object_->GetData(key);
        }
        else {
            return "error";
        }
    }
};

int main() 
{
    auto real_db = VeryHeavyDatabase();
    auto limit_db = OneShotDB(std::addressof(real_db), 2);
    std::cout << limit_db.GetData("key") << std::endl;
    std::cout << limit_db.GetData("key") << std::endl;
    std::cout << limit_db.GetData("key") << std::endl;
    return 0;
}