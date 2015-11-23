#pragma once

#include <vector>
#include "reader_interface.h"

struct frame_description
{
    std::vector<size_t> frame_dimensions;
    size_t element_size;
};

struct sequence_description // for randomization
{
    size_t id;
    size_t weight;
};

struct sequence // real data
{
    char* data;
    size_t number_of_frames;
    frame_description* frame_description;
    sequence_description* description;
};

class block_reader
{
public:
    virtual char* get(size_t offset, size_t size) = 0;
    virtual ~block_reader() = 0 {}
};

typedef std::vector<sequence_description> timeline;

class source
{
public:
    virtual timeline& get_timeline() const = 0;
    virtual std::vector<input_description_ptr> get_inputs() const = 0;
    virtual std::map<size_t /*input*/, sequence> get_sequence_by_id(size_t id) = 0;
};

class sequencer
{
public:
    virtual std::vector<input_description_ptr> get_inputs() const = 0;
    virtual std::map<size_t /*per input descriptor*/, sequence> get_next_sequence() = 0;
};

class randomizer : sequencer
{};

class image_cropper : sequencer
{};
