#pragma once

//
// Created by 沈嘉欢 on 2018-12-23.
//

#ifndef TOPOLOGICALSORT_UTIL_H
#define TOPOLOGICALSORT_UTIL_H

#include <set>
#include <iostream>
#include "../DAG.h"

std::set<Plan> getPlan(DAG &graph, size_t semesterCount);

std::tuple<std::vector<Lesson>, int, int, bool> input();

#endif //TOPOLOGICALSORT_UTIL_H
