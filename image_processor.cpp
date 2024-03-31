#include <iostream>
#include <filesystem>
#include <memory>
#include <map>
#include "image/BMP.h"
#include "image/Image.h"
#include "factories/CropFactory.h"
#include "factories/GrayscaleFactory.h"
#include "factories/NegativeFactory.h"
#include "factories/SharpeningFactory.h"
#include "factories/EdgeFactory.h"
#include "factories/BlurFactory.h"
#include "factories/OilFactory.h"

using std::string;
using std::unique_ptr;

void InitializeFactories(std::map<string, unique_ptr<FilterFactory>>& factories) {
    factories["-crop"] = std::make_unique<CropFactory>();
    factories["-gs"] = std::make_unique<GrayscaleFactory>();
    factories["-neg"] = std::make_unique<NegativeFactory>();
    factories["-sharp"] = std::make_unique<SharpeningFactory>();
    factories["-edge"] = std::make_unique<EdgeFactory>();
    factories["-blur"] = std::make_unique<BlurFactory>();
    factories["-oil"] = std::make_unique<OilFactory>();
}

int main(int argc, char** argv) {
    try {
        std::map<string, unique_ptr<FilterFactory>> factories;
        InitializeFactories(factories);

        if (argc == 1) {
            std::cout << "Launch format description:\n"
                         "{program name} {input_path} {output_path} [-{filter name 1} "
                         "[filter parameter 1] [filter parameter 2] ...] [-{filter name 2} "
                         "[filter parameter 1] [filter parameter 2] ...] ...\n\n";
            std::cout << "Here are descriptions of possible filters:\n";
            for (auto& factory : factories) {
                std::cout << factory.first << ": ";
                factory.second->PrintHelp();
                std::cout << std::endl;
            }
            std::cout << "\nProgram usage example:\n"
                         "./image_processor input.bmp /tmp/output.bmp -crop 800 600 -gs -blur 0.5"
                      << std::endl;
            return 0;
        }

        if (argc == 2) {
            throw std::invalid_argument("Output path for image must be specified.");
        }

        string input_path = argv[1];
        string output_path = argv[2];

        BMP bmp{input_path};
        Image image = bmp.ConvertToImage();

        std::vector<unique_ptr<Filter>> filters{};
        std::string filter_name;
        std::vector<string> filter_args{};

        auto create_filter = [&filters, &filter_name, &filter_args, &factories]() {
            auto it = factories.find(filter_name);
            if (filter_name.empty()) {
                if (filter_args.empty()) {
                    return;
                }
                throw std::invalid_argument("No filter was specified for first arguments.");
            }
            if (it == factories.end()) {
                throw std::invalid_argument("Unknown filter name: " + filter_name);
            }
            filters.push_back(it->second->Create(filter_args));
        };

        for (int i = 3; i < argc; i++) {
            if (argv[i][0] == '-') {
                create_filter();
                filter_name = argv[i];
                filter_args.clear();
            } else {
                filter_args.push_back(argv[i]);
            }
        }
        create_filter();

        for (unique_ptr<Filter>& f : filters) {
            image = f->Apply(image);
        }

        bmp.UpdateFromImage(image);
        bmp.ExportBMP(output_path);
    } catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
    return 0;
}
