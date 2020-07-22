#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING_LENGTH 7

struct package {
    char *id;
    int weigth;
};

typedef struct package Package;

struct office {
    int packages_count;
    Package *packages;
    int max_weight;
    int min_wight;
};

typedef struct office Office;

struct town {
    char *name;
    int offices_count;
    Office *offices;
};

typedef struct town Town;

void print_all_packages(Town *town) {
    int offices_count = town->offices_count;
    Office *offices = town->offices;

    printf("%s:\n", town->name);

    for (int j = 0; j < offices_count; ++j) {
        Office office = offices[j];
        int packages_count = office.packages_count;
        Package *packages = office.packages;

        printf("\t%d:\n", j);

        for (int k = 0; k < packages_count; ++k) {
            Package package = packages[k];
            printf("\t\t%s\n", package.id);
        }
    }
}

void send_all_acceptable_packages(Town *source, int source_office_index,
                                  Town *target, int target_office_index) {
    for (int i = 0; i < source->offices[source_office_index].packages_count;) {
        if (source->offices[source_office_index].packages[i].weigth >=
                target->offices[target_office_index].min_wight &&
            source->offices[source_office_index].packages[i].weigth <=
                target->offices[target_office_index].max_weight) {
            // Allocate memeory for the incoming package
            if (target->offices[target_office_index].packages_count == 0) {
                target->offices[target_office_index].packages =
                    (Package *)malloc(sizeof(Package));
            } else {
                target->offices[target_office_index].packages =
                    (Package *)realloc(
                        target->offices[target_office_index].packages,
                        (target->offices[target_office_index].packages_count +
                         1) *
                            sizeof(Package));
            }

            // Alocate momory for the id in the target
            target->offices[target_office_index]
                .packages[target->offices[target_office_index].packages_count]
                .id = (char *)calloc(
                strlen(source->offices[source_office_index].packages[i].id),
                sizeof(char));

            // Copy the id from the source to target
            strcpy(target->offices[target_office_index]
                       .packages[target->offices[target_office_index]
                                     .packages_count]
                       .id,
                   source->offices[source_office_index].packages[i].id);
            // Copy the weight from the source to target
            target->offices[target_office_index]
                .packages[target->offices[target_office_index].packages_count]
                .weigth =
                source->offices[source_office_index].packages[i].weigth;

            // Increase the number of packages of the target
            // After a transition
            ++(target->offices[target_office_index].packages_count);

            // Shift every element to the left starting with i
            for (int j = i;
                 j < source->offices[source_office_index].packages_count - 1;
                 ++j) {
                strcpy(source->offices[source_office_index].packages[j].id,
                       source->offices[source_office_index].packages[j + 1].id);
                source->offices[source_office_index].packages[j].weigth =
                    source->offices[source_office_index].packages[j + 1].weigth;
            }

            // Decrease the number of packages of the source office
            // If package is transfered
            --(source->offices[source_office_index].packages_count);
        } else {
            ++i;
        }
    }
}

Town town_with_most_packages(Town *towns, int towns_count) {
    Town town;
    int max = 0;

    for (int i = 0; i < towns_count; ++i) {
        int total_packages = 0;

        for (int j = 0; j < towns[i].offices_count; ++j) {
            total_packages += towns[i].offices[j].packages_count;
        }

        if (total_packages > max) {
            max = total_packages;
            town = towns[i];
        }
    }

    return town;
}

Town *find_town(Town *towns, int towns_count, char *name) {
    for (int i = 0; i < towns_count; ++i) {
        if (strcmp(towns[i].name, name) == 0) {
            return &towns[i];
        }
    }

    return NULL;
}

int main() {
    int towns_count;
    scanf("%d", &towns_count);

    Town *towns = (Town *)calloc(towns_count, sizeof(Town));

    for (int i = 0; i < towns_count; ++i) {
        towns[i].name = (char *)calloc(MAX_STRING_LENGTH, sizeof(char));
        scanf("%s", towns[i].name);
        scanf("%d", &towns[i].offices_count);
        towns[i].offices =
            (Office *)calloc(towns[i].offices_count, sizeof(Office));

        for (int j = 0; j < towns[i].offices_count; ++j) {
            scanf("%d%d%d", &towns[i].offices[j].packages_count,
                  &towns[i].offices[j].min_wight,
                  &towns[i].offices[j].max_weight);
            towns[i].offices[j].packages = (Package *)calloc(
                towns[i].offices[j].packages_count, sizeof(Package));

            for (int k = 0; k < towns[i].offices[j].packages_count; ++k) {
                towns[i].offices[j].packages[k].id =
                    (char *)calloc(MAX_STRING_LENGTH, sizeof(char));
                scanf("%s", towns[i].offices[j].packages[k].id);
                scanf("%d", &towns[i].offices[j].packages[k].weigth);
            }
        }
    }

    int queries;
    scanf("%d", &queries);

    char town_name[MAX_STRING_LENGTH];

    while (queries--) {
        int type;
        scanf("%d", &type);
        switch (type) {
            case 1:
                scanf("%s", town_name);
                Town *t = find_town(towns, towns_count, town_name);
                print_all_packages(t);
                break;
            case 2:
                scanf("%s", town_name);
                Town *source = find_town(towns, towns_count, town_name);
                int source_index;
                scanf("%d", &source_index);
                scanf("%s", town_name);
                Town *target = find_town(towns, towns_count, town_name);
                int target_index;
                scanf("%d", &target_index);
                send_all_acceptable_packages(source, source_index, target,
                                             target_index);
                break;
            case 3:
                printf("Town with the most number of packages is %s\n",
                       town_with_most_packages(towns, towns_count).name);
                break;
        }
    }

    return 0;
}