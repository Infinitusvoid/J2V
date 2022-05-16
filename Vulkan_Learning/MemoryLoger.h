#pragma once

#include <iostream>
#include <memory>

struct AllocationsMetrics
{
    uint32_t TotalAllocated = 0;
    uint32_t TotalFreed = 0;

    uint32_t CurrentUsage()
    {
        return TotalAllocated - TotalFreed;
    }
};

static AllocationsMetrics s_allocationsMetrics;

void* operator new(size_t size)
{
    s_allocationsMetrics.TotalAllocated += size;
    return malloc(size);
}

void operator delete(void* memory, size_t size)
{
    s_allocationsMetrics.TotalFreed += size;
    free(memory);
}

static void PrintMemoryUsage()
{
    std::cout << "Memory usage: " << s_allocationsMetrics.CurrentUsage() << " bytes\n";
}