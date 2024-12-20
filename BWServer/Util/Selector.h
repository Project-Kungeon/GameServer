#pragma once
#include "pch.h"

class Selector {
private:
    std::vector<std::function<bool()>> nodes;

public:
    void addNode(std::function<bool()> node) {
        nodes.push_back(node);
    }

    template<typename F, typename... Args>
    void addLambda(F&& lambda, Args&&... args) {
        nodes.push_back([=]() { return lambda(args...); });
    }

    bool execute() {
        for (const auto& node : nodes) {
            if (node()) {
                return true;  // 노드 실행 성공, Selector 전체 성공으로 종료
            }
        }
        return false;  // 모든 노드가 실패한 경우, Selector 전체 실패
    }
};