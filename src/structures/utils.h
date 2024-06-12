#pragma once

#define CONCAT_(pred, center, succ) pred##center##succ
#define CONCAT(pred, center, succ) CONCAT_(pred, center, succ)
