#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

/* DnD 5e Character Creator

    GOALS:
    ✓ Create structs for stats/bonuses
    ✓ Create a struct to represent a sheet
    ✓ Create function to return a randomly rolled stat
    ✓ Fix incorrect stat bonus with negative stat levels
    ✓ Store stats as named members of sheet
    ✗ Store skills as named members of stats
    ✓ Create function to populate skill bonuses

    ✓ Create function to roll all stats
    - Create meta structure for storing skills under one parent stat
    - Fix UpdateAllSkills() check (can't check for NULL?)
    - Create function to roll skill check
    - Test SetSkillProficiency() w/ roll function

    - Store each sheet as a file on the computer

    NOTES:
    Don't entirely recreate the sheet from the ground up,
    focus on broad systems like stats and character motivations
    (that are coincidentally easier to implement hehe)

    Systems to recreate:
    ✓ Character Info (including motivations)
    ✓ Stats with Manual Rolls (Roll 3 or 4d6, drop the lowest)
    - Skills w/ proficiency
    - Saving throws w/ proficiency
    - Hit Points/Dice
    
    Learn "proper" format to store files

*/

struct s_stat{
    int level;
    int bonus;
};

struct s_skill{
    bool proficient;
    int bonus;
};

struct s_str_skills{
    
};

struct s_sheet{
    // Info
    char name[32];
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

struct s_stat RollStat(int);
struct s_skill SetSkillDefault(struct s_stat *);
void SetSkillProficiency(struct s_skill *, bool);
void RollAllStats(struct s_sheet *, int);
void UpdateAllSkills(struct s_sheet *);

int main(){
    srand(time(NULL));
    struct s_sheet *p_sheet = (struct s_sheet *) malloc(sizeof(struct s_sheet));

    RollAllStats(p_sheet, 4);
    UpdateAllSkills(p_sheet);

    free(p_sheet);
    return 0;
}

// Returns a randomly rolled stat, given a quantity of dice
struct s_stat RollStat(int diceCount){

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

// Returns a skill with false proficiency and bonus derived from parent stat
struct s_skill SetSkillDefault(struct s_stat *parent){
    struct s_skill newSkill = {false, parent->bonus};
    return newSkill;
}

// Returns a skill with proficiency modded, given an existing skill
void SetSkillProficiency(struct s_skill *inputSkill, bool condition){
    inputSkill->proficient = condition;
}

// Randomly rolls every stat on the sheet
void RollAllStats(struct s_sheet *sheet, int diceCount){
    struct s_stat *p_strength = &sheet->strength;

    for (int i = 0; i < 6; i++){
        *(p_strength + i) = RollStat(diceCount);
        printf("Level: %i | Bonus: %i\n", (p_strength + i)->level, (p_strength + i)->bonus);
    }    
}

void UpdateAllSkills(struct s_sheet *sheet){
    // Get pointer to first skill (athletics) and to first parent stat
    struct s_stat *p_currentStat = &sheet->strength;
    struct s_skill *p_currentSkill = &sheet->athletics;

    // Empty Stat Check
    for (int i = 0; i < 6; i++){
        if ((p_currentStat + i) == NULL){
            printf("Error: Invalid stat detected.");
            return;
        }
    }

    // For each category of skill, call SetSkillDefault()

    // Strength
    *p_currentSkill = SetSkillDefault(p_currentStat);
    printf("STR Skill Bonus: %i\n", p_currentSkill->bonus);

    // Dexterity
    p_currentStat = &sheet->dexterity;
    p_currentSkill = &sheet->acrobatics;

    for (int i = 0; i < 3; i++){
        *(p_currentSkill + i) = SetSkillDefault(p_currentStat);
        printf("DEX Skill Bonus: %i\n", p_currentSkill->bonus);
    }

    // Intelligence
    p_currentStat = &sheet->intelligence;
    p_currentSkill = &sheet->arcana;

    for (int i = 0; i < 5; i++){
        *(p_currentSkill + i) = SetSkillDefault(p_currentStat);
        printf("INT Skill Bonus: %i\n", p_currentSkill->bonus);
    }

    // Wisdom
    p_currentStat = &sheet->wisdom;
    p_currentSkill = &sheet->animal;

    for (int i = 0; i < 5; i++){
        *(p_currentSkill + i) = SetSkillDefault(p_currentStat);
        printf("WIS Skill Bonus: %i\n", p_currentSkill->bonus);
    }

    // Charisma
    p_currentStat = &sheet->charisma;
    p_currentSkill = &sheet->deception;

    for (int i = 0; i < 4; i++){
        *(p_currentSkill + i) = SetSkillDefault(p_currentStat);
        printf("CHA Skill Bonus: %i\n", p_currentSkill->bonus);
    }
}




