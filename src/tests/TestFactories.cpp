#include <vector>
#include <string>
#include <exception>
#include <memory>
#include "tests/TestFailedException.h"
#include "factories/BlurFactory.h"
#include "factories/CropFactory.h"
#include "factories/EdgeFactory.h"
#include "factories/GrayscaleFactory.h"
#include "factories/NegativeFactory.h"
#include "factories/OilFactory.h"

using std::make_shared;
using std::pair;
using std::shared_ptr;
using std::string;
using std::vector;

struct TestGroup {
    shared_ptr<FilterFactory> factory_ptr_;
    vector<vector<string>> args_;
    string factory_name_;

    TestGroup(shared_ptr<FilterFactory> ptr, const vector<vector<string>> &args, const string &factory_name)
        : factory_ptr_(ptr), args_(args), factory_name_(factory_name) {
    }
};

string ArgsToString(const vector<string> &args) {
    string result = "{";
    for (int i = 0; i < args.size(); i++) {
        result += "\"" + args[i] + "\"";
        if (i + 1 != args.size()) {
            result += ", ";
        }
    }
    result += "}";
    return result;
}

void TestValidArguments() {
    vector<TestGroup> test_groups = {
        {make_shared<BlurFactory>(), {{"0"}, {"0.001"}, {"123123"}}, "Blur Factory"},
        {make_shared<CropFactory>(), {{"100", "0"}, {"0", "0"}, {"100000", "100000"}}, "Crop Factory"},
        {make_shared<EdgeFactory>(), {{"0"}, {"1"}, {"0.5"}, {"0.999"}}, "Edge Factory"},
        {make_shared<GrayscaleFactory>(), {{}}, "Grayscale Factory"},
        {make_shared<NegativeFactory>(), {{}}, "Negative Factory"},
        {make_shared<OilFactory>(), {{"1", "1"}, {"123", "321"}}, "Oil Factory"}};
    for (auto &test : test_groups) {
        for (auto &current_args : test.args_) {
            try {
                test.factory_ptr_->Create(current_args);
            } catch (std::invalid_argument &ex) {
                throw TestFailedException(test.factory_name_ + ": Failed FilterFactory::Create with valid arguments " +
                                          ArgsToString(current_args) +
                                          " with following exception: " + string(ex.what()));
            }
        }
    }
}

void TestInvalidArguments() {
    vector<TestGroup> test_groups = {
        {make_shared<BlurFactory>(), {{""}, {"lol"}, {"-100000"}, {}, {"1", "1"}}, "Blur Factory"},
        {make_shared<CropFactory>(), {{"-1", "100"}, {".30", "10"}, {"20"}, {}}, "Crop Factory"},
        {make_shared<EdgeFactory>(), {{"-0.1"}, {"1.001"}, {"lll"}, {"110"}, {""}, {}}, "Edge Factory"},
        {make_shared<GrayscaleFactory>(), {{"1"}, {""}, {"i", "am", "bored"}}, "Grayscale Factory"},
        {make_shared<NegativeFactory>(), {{"0"}, {"", ""}}, "Negative Factory"},
        {make_shared<OilFactory>(), {{"0", "1"}, {"1", "0"}, {}, {"1"}, {"1", "2", "3"}}, "Oil Factory"}};

    for (auto &test : test_groups) {
        for (auto &current_args : test.args_) {
            try {
                test.factory_ptr_->Create(current_args);
            } catch (std::invalid_argument &ex) {
                continue;
            }
            throw TestFailedException(test.factory_name_ + ": Successfuly created with invalid arguments " +
                                      ArgsToString(current_args));
        }
    }
}

int main() {
    TestValidArguments();
    TestInvalidArguments();

    return 0;
}