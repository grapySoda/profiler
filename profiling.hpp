// profiling.h (Header-only implementation)

#ifndef PROFILING_H
#define PROFILING_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <chrono>
#include <cmath>

class Profiling {
    public:
        Profiling(const std::string& name) : name_(name) {
            auto it = std::find_if(profiles_.begin(), profiles_.end(),
                                [name](const Profile& p) { return p.name == name; });

            if (it == profiles_.end()) {
                profiles_.emplace_back(name);
                current_profile_ = &profiles_.back();
            } else {
                current_profile_ = &(*it);
            }
        }

        ~Profiling() {}

        void start() {
            if (current_profile_->running) {
                std::cerr << "Error: Profiling already running for " << current_profile_->name << std::endl;
                return;
            }
            current_profile_->start_time = std::chrono::high_resolution_clock::now();
            current_profile_->running = true;
            // Ensure current_profiling is set to this before using it
            // current_profiling = this;
        }

        void stop() {
            if (!current_profile_->running) {
                std::cerr << "Error: Profiling not running for " << current_profile_->name << std::endl;
                return;
            }
            auto end_time = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end_time - current_profile_->start_time;

            current_profile_->current_durations = duration.count();

            current_profile_->durations.push_back(duration.count());
            current_profile_->running = false;
            // Ensure current_profiling is set to nullptr after stopping
            // current_profiling CW = nullptr;
        }

        static std::string report() {
            std::string result;

            for (const auto& profile : profiles_) {
                result += "---\n" + profile.name + ": Average execution time: " +
                        std::to_string(calculateAverage(profile.durations)) + " ms\n" +
                        profile.name + ": Standard Deviation: " +
                        std::to_string(calculateStandardDeviation(profile.durations)) + "\n";
            }

            return result;
        }

        double getCurrentDuration() { return current_profile_->current_durations; }
        double getAverageTime() { return calculateAverage(current_profile_->durations); }

    private:
        struct Profile {
            Profile(const std::string& profileName) : name(profileName) {}
            
            bool running;
            std::string name;
            std::chrono::high_resolution_clock::time_point start_time;
            std::vector<double> durations;
            double current_durations;
        };

        static std::vector<Profile> profiles_;
        static Profile* current_profile_;

        std::string name_;

        static double calculateAverage(const std::vector<double>& data) {
            double sum = 0.0;
            for (const auto& value : data) {
                sum += value;
            }
            return sum / data.size();
        }

        static double calculateStandardDeviation(const std::vector<double>& data) {
            double mean = calculateAverage(data);
            double variance = 0.0;

            for (const auto& value : data) {
                variance += std::pow(value - mean, 2);
            }

            variance /= data.size();

            return std::sqrt(variance);
        }
};

// Initialize static members
std::vector<Profiling::Profile> Profiling::profiles_;
Profiling::Profile* Profiling::current_profile_;

#endif // PROFILING_H
