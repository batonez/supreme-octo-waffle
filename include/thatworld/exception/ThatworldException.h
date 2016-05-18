#pragma once

#include <glade/exception/GladeException.h>

class ThatworldException: public GladeException
{
  public:
    ThatworldException(): GladeException() {}
    ThatworldException(std::string &message): GladeException(message) {}
    ThatworldException(const char *message): GladeException(message) {}
};
