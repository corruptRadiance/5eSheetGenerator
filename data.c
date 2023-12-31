#include <stdbool.h>
#include <math.h>

struct s_stat{
    int level;
    int bonus;
};

struct s_skill{
    bool proficient;
    int bonus;
};

struct s_sheet{
    // Character Info
    char playerName[32];
    char characterName[32];
    char pronouns[32];
    char personality[256];

    // Stats
    int level;
    int proficiency;
    struct s_stat strength;
    struct s_stat dexterity;
    struct s_stat constitution;
    struct s_stat intelligence;
    struct s_stat wisdom;
    struct s_stat charisma;

    // Skills
    // Strength
    struct s_skill athletics;
    
    // Dexterity
    struct s_skill acrobatics;
    struct s_skill sleight;
    struct s_skill stealth;

    // Intelligence
    struct s_skill arcana;
    struct s_skill history;
    struct s_skill investigation;
    struct s_skill nature;
    struct s_skill religion;

    // Wisdom
    struct s_skill animal;
    struct s_skill insight;
    struct s_skill medicine;
    struct s_skill perception;
    struct s_skill survival;

    // Charisma
    struct s_skill deception;
    struct s_skill intimidation;
    struct s_skill performance;
    struct s_skill persuasion;
};

struct s_stat InitializeStat(){
    struct s_stat initializedStat = {-1, -1};
    return initializedStat;
}

struct s_stat RollForStat(int diceCount){

    int results[diceCount];
    int swapCount;

    // Roll four random numbers 1-6
    for (int i = 0; i < diceCount; i++){
        results[i] = (rand() % 6) + 1;
    }

    // Sort
    do{
        swapCount = 0;
        for (int i = 1; i < diceCount; i++){
            int t = results[i];

            if (results[i - 1] > t){
                results[i] = results[i - 1];
                results[i - 1] = t;
                swapCount++;
            }
        }
    }while (swapCount > 0);

    // Sum Highest Results
    float sum = 0;
    for (int i = 1; i < diceCount; i++){
        sum += results[i];
    }
    
    // Calculate Bonus
    float bonus = floor((sum - 10) / 2);

    struct s_stat rolled = {sum, bonus};
    return rolled;
}

struct s_skill NewSkill(struct s_stat *parent, bool proficiency){
    struct s_skill newSkill = {proficiency, parent->bonus};
    return newSkill;
}

struct s_sheet *NewSheet(){
    // Allocate Memory
    struct s_sheet *sheet = (struct s_sheet *) malloc(sizeof(struct s_sheet));

    // Initialize Character Info
    strncpy(sheet->playerName,    "", sizeof(sheet->playerName));
    strncpy(sheet->characterName, "", sizeof(sheet->characterName));
    strncpy(sheet->pronouns,      "", sizeof(sheet->pronouns));
    strncpy(sheet->personality,   "", sizeof(sheet->personality));

    // Initialize Stats
    sheet->level = 1;
    sheet->proficiency = 2;

    struct s_stat *currentStat = &sheet->strength;
    for (int i = 0; i < 6; i++){
        *(currentStat + i) = InitializeStat();
    }

    return sheet;
}

void RollAllStats(struct s_sheet *sheet, int diceCount){
    struct s_stat *p_strength = &sheet->strength;

    for (int i = 0; i < 6; i++){
        *(p_strength + i) = RollForStat(diceCount);
    }    
}

void UpdateAllSkills(struct s_sheet *sheet){
    // Get pointer to first skill (athletics) and to first parent stat
    struct s_stat *p_currentStat = &sheet->strength;
    struct s_skill *p_currentSkill = &sheet->athletics;

    // Empty Stat Check
    for (int i = 0; i < 6; i++){
        if ((p_currentStat + i)->level == -1){
            printf("Error: Invalid stat detected.\n");
            return;
        }
    }

    // For each category of skill, call NewSkill()

    // Strength
    *p_currentSkill = NewSkill(p_currentStat, p_currentSkill->proficient);

    // Dexterity
    p_currentStat = &sheet->dexterity;
    p_currentSkill = &sheet->acrobatics;

    for (int i = 0; i < 3; i++){
        *(p_currentSkill + i) = NewSkill(p_currentStat, p_currentSkill->proficient);
    }

    // Intelligence
    p_currentStat = &sheet->intelligence;
    p_currentSkill = &sheet->arcana;

    for (int i = 0; i < 5; i++){
        *(p_currentSkill + i) = NewSkill(p_currentStat, p_currentSkill->proficient);
    }

    // Wisdom
    p_currentStat = &sheet->wisdom;
    p_currentSkill = &sheet->animal;

    for (int i = 0; i < 5; i++){
        *(p_currentSkill + i) = NewSkill(p_currentStat, p_currentSkill->proficient);
    }

    // Charisma
    p_currentStat = &sheet->charisma;
    p_currentSkill = &sheet->deception;

    for (int i = 0; i < 4; i++){
        *(p_currentSkill + i) = NewSkill(p_currentStat, p_currentSkill->proficient);
    }
}

void SetSkillProficiency(struct s_skill input, bool condition){
    input.proficient = condition;
}

