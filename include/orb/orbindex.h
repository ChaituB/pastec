/*****************************************************************************
 * Copyright (C) 2014 Visualink
 *
 * Authors: Adrien Maglo <adrien@visualink.io>
 *
 * This file is part of Pastec.
 *
 * Pastec is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Pastec is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Pastec.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/

#ifndef PASTEC_ORBINDEX_H
#define PASTEC_ORBINDEX_H

#include <fstream>
#include <string>

#include <sys/types.h>

#include <map>
#include <vector>
#include <list>
#ifndef __APPLE__
#include <tr1/unordered_map>
#else
#include <unordered_map>
#endif

#include <hit.h>
#include <backwardindexreaderaccess.h>
#include <index.h>

using namespace std;
#ifndef __APPLE__
using namespace std::tr1;
#endif


#define NB_VISUAL_WORDS 1000000
#define BACKWARD_INDEX_ENTRY_SIZE 10

class ORBIndex : public Index
{
public:
    ORBIndex(string indexPath, bool buildForwardIndex);
    virtual ~ORBIndex();
    void getImagesWithVisualWords(unordered_map<u_int32_t, list<Hit> > &imagesReqHits,
                                  unordered_map<u_int32_t, vector<Hit> > &indexHitsForReq);
    unsigned getWordNbOccurences(unsigned i_wordId);
    unsigned countTotalNbWord(unsigned i_imageId);
    unsigned getTotalNbIndexedImages();
    u_int32_t addImage(unsigned i_imageId, list<HitForward> hitList);
    u_int32_t removeImage(const unsigned i_imageId);
    u_int32_t getImageWords(const unsigned i_imageId, unordered_map<u_int32_t, list<Hit> > &hitList);
    u_int32_t write(string backwardIndexPath);
    u_int32_t clear();
    u_int32_t load(string backwardIndexPath);
    u_int32_t getImageIds(vector<u_int32_t> &imageIds);
    void readLock();
    void unlock();

private:
    bool readIndex(string backwardIndexPath);

    u_int64_t nbOccurences[NB_VISUAL_WORDS];
    u_int64_t totalNbRecords;
    bool buildForwardIndex;

    unordered_map<u_int64_t, unsigned> nbWords;
    unordered_map<u_int64_t, vector<unsigned> > forwardIndex;
    vector<Hit> indexHits[NB_VISUAL_WORDS];

    pthread_rwlock_t rwLock;
};

#endif // PASTEC_ORBINDEX_H
