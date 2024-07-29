#pragma once

#define NOCOPY(CLASS)                           \
private:                                        \
CLASS(const CLASS& other) = delete;              \
CLASS& operator=(const CLASS& other) = delete;    \
CLASS(CLASS&& other) = delete;                   \
CLASS& operator=(CLASS&& other) = delete;