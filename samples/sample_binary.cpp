/*
 * Copyright 2015 Google Inc. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/reflection.h"
#include "flatbuffers/util.h"

using flatbuffers::uoffset_t;

// Example how to use FlatBuffers to create and read binary buffers.

int main(int argc, const char * argv[]) {
    std::string bfbsschema;
    if (!flatbuffers::LoadFile(argv[1], true, &bfbsschema)) {
        return 1;
    }
    auto &schema = *reflection::GetSchema(bfbsschema.c_str());
    
    std::string bfbsfile;
    if (!flatbuffers::LoadFile(argv[2], true, &bfbsfile)) {
        return 1;
    }
    const uint8_t* flatbuf = (uint8_t*)bfbsfile.c_str();
    if (flatbuffers::Verify(schema, *schema.root_table(), flatbuf, bfbsfile.length())) {
        return 0;
    } else {
        printf("Failed to verify!\n");
        return 1;
    }
}

