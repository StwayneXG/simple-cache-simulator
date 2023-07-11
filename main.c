#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int num_offset_bits;
    int num_index_bits;
    int num_tag_bits;
    int num_sets;
    int associativity;
} cache_config;

typedef struct {
    int num_hits;
    int num_misses;
    double hit_rate;
    double miss_rate;
} cache_stats;

void extract_bits(unsigned int address, cache_config config, unsigned int *tag, unsigned int *index, unsigned int *offset) {
    *offset = address & ((1 << config.num_offset_bits) - 1);
    *index = (address >> config.num_offset_bits) & ((1 << config.num_index_bits) - 1);
    *tag = (address >> (config.num_offset_bits + config.num_index_bits)) & ((1 << config.num_tag_bits) - 1);
}

void init_cache(unsigned int ***cache, cache_config config) {
    int i, j;
    *cache = (unsigned int **)malloc(config.num_sets * sizeof(unsigned int *));
    for (i = 0; i < config.num_sets; i++) {
        (*cache)[i] = (unsigned int *)malloc(config.associativity * sizeof(unsigned int));
        for (j = 0; j < config.associativity; j++) {
            (*cache)[i][j] = 0;
        }
    }
}

void cache_lookup(unsigned int address, unsigned int ***cache, cache_config config, cache_stats *stats) {
    unsigned int tag, index, offset;
    int i, j;
    extract_bits(address, config, &tag, &index, &offset);
    for (i = 0; i < config.associativity; i++) {
        if ((*cache)[index][i] == tag) {
            stats->num_hits++;
            return;
        }
    }
    stats->num_misses++;
    int line_to_replace = 0;
    if (config.associativity == 2) {
        line_to_replace = rand() % 2;
    }
    (*cache)[index][line_to_replace] = tag;
}

void print_stats(cache_stats stats) {
    printf("Number of hits: %d\n", stats.num_hits);
    printf("Number of misses: %d\n", stats.num_misses);
    printf("Hit rate: %.2f%%\n", stats.hit_rate);
    printf("Miss rate: %.2f%%\n", stats.miss_rate);
}

int main() {
    cache_config config;
    config.num_offset_bits = 5;
    config.num_index_bits = 7;
    config.num_tag_bits = 20;
    config.num_sets = pow(2, config.num_index_bits);
    config.associativity = 2;

    unsigned int **cache;
    init_cache(&cache, config);

    cache_stats stats = {0, 0, 0.0, 0.0};

    FILE *fp = fopen("MemoryTrace.txt", "r");
    if (fp == NULL) {
        printf("Failed to open file.\n");
        return -1;
    }

    unsigned int address;
    while (fscanf(fp, "%x", &address) != EOF) {
        cache_lookup(address, &cache, config, &stats);
    }
    fclose(fp);

    stats.hit_rate = 100.0 * stats.num_hits / (stats.num_hits + stats.num_misses);
    stats.miss_rate = 100.0 * stats.num_misses / (stats.num_hits + stats.num_misses);
    print_stats(stats);

    return 0;
}
