
/*
 *
 MIT License

Copyright (c) 2019 Greg Donald

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 * */

#include "blackjack.h"

const unsigned shuffle_specs[8][2] = {{95, 8},
                                      {92, 7},
                                      {89, 6},
                                      {86, 5},
                                      {84, 4},
                                      {82, 3},
                                      {81, 2},
                                      {80, 1}};

const char *const card_faces[14][4] = {{"🂡", "🂱", "🃁", "🃑"},
                                       {"🂢", "🂲", "🃂", "🃒"},
                                       {"🂣", "🂳", "🃃", "🃓"},
                                       {"🂤", "🂴", "🃄", "🃔"},
                                       {"🂥", "🂵", "🃅", "🃕"},
                                       {"🂦", "🂶", "🃆", "🃖"},
                                       {"🂧", "🂷", "🃇", "🃗"},
                                       {"🂨", "🂸", "🃈", "🃘"},
                                       {"🂩", "🂹", "🃉", "🃙"},
                                       {"🂪", "🂺", "🃊", "🃚"},
                                       {"🂫", "🂻", "🃋", "🃛"},
                                       {"🂭", "🂽", "🃍", "🃝"},
                                       {"🂮", "🂾", "🃎", "🃞"},
                                       {"🂠", "",   "",   ""}};

bool is_ace(const struct Card *card) {
    return card->value == 0;
}

bool is_ten(const struct Card *card) {
    return card->value > 8;
}

unsigned player_get_value(const struct PlayerHand *player_hand, enum CountMethod method) {
    unsigned total = 0;

    for (unsigned x = 0; x < player_hand->hand.num_cards; ++x) {
        unsigned tmp_v = player_hand->hand.cards[x].value + 1;
        unsigned v = tmp_v > 9 ? 10 : tmp_v;

        if (method == Soft && v == 1 && total < 11) {
            v = 11;
        }

        total += v;
    }

    if (method == Soft && total > 21) {
        return player_get_value(player_hand, Hard);
    }

    return total;
}

bool player_is_busted(const struct PlayerHand *player_hand) {
    return player_get_value(player_hand, Soft) > 21;
}

bool is_blackjack(const struct Hand *hand) {
    if (hand->num_cards != 2) {
        return false;
    }

    if (is_ace(&hand->cards[0]) && is_ten(&hand->cards[1])) {
        return true;
    }

    return is_ace(&hand->cards[1]) && is_ten(&hand->cards[0]);
}

bool player_can_hit(const struct PlayerHand *player_hand) {
    if (player_hand->played
        || player_hand->stood
        || 21 == player_get_value(player_hand, Hard)
        || is_blackjack(&player_hand->hand)
        || player_is_busted(player_hand)) {
        return false;
    }

    return true;
}

bool player_can_stand(const struct PlayerHand *player_hand) {
    if (player_hand->stood
        || player_is_busted(player_hand)
        || is_blackjack(&player_hand->hand)) {
        return false;
    }

    return true;
}

unsigned all_bets(const struct Game *game) {
    unsigned bets = 0;

    for (unsigned x = 0; x < game->total_player_hands; x++) {
        bets += game->player_hands[x].bet;
    }

    return bets;
}

bool player_can_split(const struct Game *game) {
    const struct PlayerHand *player_hand = &game->player_hands[game->current_player_hand];

    if (player_hand->stood || game->total_player_hands >= MAX_PLAYER_HANDS) {
        return false;
    }

    if (game->money < all_bets(game) + player_hand->bet) {
        return false;
    }

    return player_hand->hand.num_cards == 2 && player_hand->hand.cards[0].value == player_hand->hand.cards[1].value;
}

bool player_can_dbl(const struct Game *game) {
    const struct PlayerHand *player_hand = &game->player_hands[game->current_player_hand];

    if (game->money < all_bets(game) + player_hand->bet) {
        return false;
    }

    if (player_hand->stood
        || player_hand->hand.num_cards != 2
        || player_is_busted(player_hand)
        || is_blackjack(&player_hand->hand)) {
        return false;
    }

    return true;
}

void deal_card(struct Shoe *shoe, struct Hand *hand) {
    hand->cards[hand->num_cards++] = shoe->cards[shoe->current_card++];
}

bool player_is_done(struct Game *game, struct PlayerHand *player_hand) {
    if (player_hand->played
        || player_hand->stood
        || is_blackjack(&player_hand->hand)
        || player_is_busted(player_hand)
        || 21 == player_get_value(player_hand, Soft)
        || 21 == player_get_value(player_hand, Hard)) {
        player_hand->played = true;

        if (!player_hand->payed && player_is_busted(player_hand)) {
            player_hand->payed = true;
            player_hand->status = Lost;
            game->money -= player_hand->bet;
        }

        return true;
    }

    return false;
}

bool more_hands_to_play(const struct Game *game) {
    return game->current_player_hand < game->total_player_hands - 1;
}

bool need_to_play_dealer_hand(const struct Game *game) {
    const struct PlayerHand *player_hand;

    for (unsigned x = 0; x < game->total_player_hands; ++x) {
        player_hand = &game->player_hands[x];

        if (!(player_is_busted(player_hand) || is_blackjack(&player_hand->hand))) {
            return true;
        }
    }

    return false;
}

unsigned dealer_get_value(const struct DealerHand *dealer_hand, enum CountMethod method) {
    unsigned v = 0;
    unsigned total = 0;
    unsigned tmp_v;

    for (unsigned x = 0; x < dealer_hand->hand.num_cards; ++x) {
        if (x == 1 && dealer_hand->hide_down_card) {
            continue;
        }

        tmp_v = dealer_hand->hand.cards[x].value + 1;
        v = tmp_v > 9 ? 10 : tmp_v;

        if (method == Soft && v == 1 && total < 11) {
            v = 11;
        }

        total += v;
    }

    if (method == Soft && total > 21) {
        return dealer_get_value(dealer_hand, Hard);
    }

    return total;
}

bool dealer_is_busted(const struct DealerHand *dealer_hand) {
    return dealer_get_value(dealer_hand, Soft) > 21;
}

void normalize_bet(struct Game *game) {
    if (game->current_bet < MIN_BET) {
        game->current_bet = MIN_BET;
    } else if (game->current_bet > MAX_BET) {
        game->current_bet = MAX_BET;
    }

    if (game->current_bet > game->money) {
        game->current_bet = game->money;
    }
}

void save_game(const struct Game *game) {
    FILE *fp = fopen(SAVE_FILE, "w");

    if (fp != NULL) {
        fprintf(fp, "%u\n%u\n%u\n", game->num_decks, game->money, game->current_bet);
        fclose(fp);
    }
}

void load_game(struct Game *game) {
    FILE *fp = fopen(SAVE_FILE, "r");

    if (fp != NULL) {
        char buffer[32];

        fgets(buffer, sizeof(buffer), fp);
        game->num_decks = strtoul(buffer, NULL, 0);

        fgets(buffer, sizeof(buffer), fp);
        game->money = strtoul(buffer, NULL, 0);

        fgets(buffer, sizeof(buffer), fp);
        game->current_bet = strtoul(buffer, NULL, 0);

        fclose(fp);
    }
}

void pay_hands(struct Game *game) {
    struct DealerHand *dealer_hand = &game->dealer_hand;
    unsigned dhv = dealer_get_value(dealer_hand, Soft);
    bool dhb = dealer_is_busted(dealer_hand);
    struct PlayerHand *player_hand;
    unsigned phv;

    for (unsigned x = 0; x < game->total_player_hands; ++x) {
        player_hand = &game->player_hands[x];

        if (player_hand->payed) {
            continue;
        }

        player_hand->payed = true;

        phv = player_get_value(player_hand, Soft);

        if (dhb || phv > dhv) {
            if (is_blackjack(&player_hand->hand)) {
                player_hand->bet = (unsigned) (player_hand->bet * 1.5);
            }

            game->money += player_hand->bet;
            player_hand->status = Won;
        } else if (phv < dhv) {
            game->money -= player_hand->bet;
            player_hand->status = Lost;
        } else {
            player_hand->status = Push;
        }
    }

    normalize_bet(game);
    save_game(game);
}

void play_dealer_hand(struct Game *game) {
    struct DealerHand *dealer_hand = &game->dealer_hand;
    unsigned soft_count;
    unsigned hard_count;

    if (is_blackjack(&dealer_hand->hand)) {
        dealer_hand->hide_down_card = false;
    }

    if (!need_to_play_dealer_hand(game)) {
        pay_hands(game);
        return;
    }

    dealer_hand->hide_down_card = false;

    soft_count = dealer_get_value(dealer_hand, Soft);
    hard_count = dealer_get_value(dealer_hand, Hard);

    while (soft_count < 18 && hard_count < 17) {
        deal_card(&game->shoe, &dealer_hand->hand);
        soft_count = dealer_get_value(dealer_hand, Soft);
        hard_count = dealer_get_value(dealer_hand, Hard);
    }

    pay_hands(game);
}

void clear(void) {
    system("export TERM=linux; clear");
}

void draw_dealer_hand(const struct Game *game) {
    const struct DealerHand *dealer_hand = &game->dealer_hand;
    const struct Card *card;

    printf(" ");

    for (unsigned i = 0; i < dealer_hand->hand.num_cards; ++i) {
        if (i == 1 && dealer_hand->hide_down_card) {
            printf("%s ", game->card_faces[13][0]);
        } else {
            card = &dealer_hand->hand.cards[i];
            printf("%s ", game->card_faces[card->value][card->suit]);
        }
    }

    printf(" ⇒  %u", dealer_get_value(dealer_hand, Soft));
}

void player_draw_hand(const struct Game *game, unsigned index) {
    const struct PlayerHand *player_hand = &game->player_hands[index];

    printf(" ");

    for (unsigned i = 0; i < player_hand->hand.num_cards; ++i) {
        const struct Card *card = &player_hand->hand.cards[i];
        printf("%s ", game->card_faces[card->value][card->suit]);
    }

    printf(" ⇒  %u  ", player_get_value(player_hand, Soft));

    if (player_hand->status == Lost) {
        printf("-");
    } else if (player_hand->status == Won) {
        printf("+");
    }

    printf("$%.2f", (double) (player_hand->bet / 100.0));

    if (!player_hand->played && index == game->current_player_hand) {
        printf(" ⇐");
    }

    printf("  ");

    if (player_hand->status == Lost) {
        printf(player_is_busted(player_hand) ? "Busted!" : "Lose!");
    } else if (player_hand->status == Won) {
        printf(is_blackjack(&player_hand->hand) ? "Blackjack!" : "Won!");
    } else if (player_hand->status == Push) {
        printf("Push");
    }

    printf("\n\n");
}

void draw_hands(const struct Game *game) {
    clear();
    printf("\n Dealer: \n");
    draw_dealer_hand(game);
    printf("\n\n Player $%.2f:\n", (double) (game->money / 100.0));

    for (unsigned x = 0; x < game->total_player_hands; x++) {
        player_draw_hand(game, x);
    }
}

bool need_to_shuffle(const struct Game *game) {
    unsigned used = (unsigned) ((game->shoe.current_card / (double) game->shoe.num_cards) * 100.0);

    for (unsigned x = 0; x < MAX_DECKS; ++x) {
        if (game->num_decks == game->shuffle_specs[x][1] && used > game->shuffle_specs[x][0]) {
            return true;
        }
    }

    return false;
}

void swap(struct Card *a, struct Card *b) {
    struct Card tmp = *a;
    *a = *b;
    *b = tmp;
}

void shuffle(struct Shoe *shoe) {
    for (unsigned x = 0; x < 7; x++) {
        for (unsigned i = shoe->num_cards - 1; i > 0; i--) {
            swap(&shoe->cards[i], &shoe->cards[myrand(0, shoe->num_cards - 1)]);
        }
    }

    shoe->current_card = 0;
}

unsigned myrand(unsigned min, unsigned max) {
    double scaled = rand() / (RAND_MAX + 1.0);
    return (unsigned) ((max - min + 1) * scaled + min);
}

bool dealer_upcard_is_ace(const struct DealerHand *dealer_hand) {
    return is_ace(&dealer_hand->hand.cards[0]);
}

void insure_hand(struct Game *game) {
    struct PlayerHand *player_hand = &game->player_hands[game->current_player_hand];

    player_hand->bet /= 2;
    player_hand->played = true;
    player_hand->payed = true;
    player_hand->status = Lost;
    game->money -= player_hand->bet;

    draw_hands(game);
    bet_options(game);
}

void no_insurance(struct Game *game) {
    struct DealerHand *dealer_hand = &game->dealer_hand;
    struct PlayerHand *player_hand;

    if (is_blackjack(&dealer_hand->hand)) {
        dealer_hand->hide_down_card = false;

        pay_hands(game);
        draw_hands(game);
        bet_options(game);
        return;
    }

    player_hand = &game->player_hands[game->current_player_hand];

    if (player_is_done(game, player_hand)) {
        play_dealer_hand(game);
        draw_hands(game);
        bet_options(game);
        return;
    }

    draw_hands(game);
    player_get_action(game);
}

void ask_insurance(struct Game *game) {
    printf(" Insurance?  (Y) Yes  (N) No\n");

    while (true) {
        char c = (char) getchar();

        switch (c) {
            case 'y':
                insure_hand(game);
                break;
            case 'n':
                no_insurance(game);
                break;
            default:
                clear();
                draw_hands(game);
                ask_insurance(game);
                break;
        }

        break;
    }
}

void deal_new_hand(struct Game *game) {
    struct PlayerHand player_hand = {.bet=game->current_bet};
    struct DealerHand *dealer_hand = &game->dealer_hand;
    struct Shoe *shoe = &game->shoe;

    if (need_to_shuffle(game)) {
        shuffle(shoe);
    }

    dealer_hand->hide_down_card = true;
    dealer_hand->hand.num_cards = 0;

    deal_card(shoe, &player_hand.hand);
    deal_card(shoe, &dealer_hand->hand);
    deal_card(shoe, &player_hand.hand);
    deal_card(shoe, &dealer_hand->hand);

    game->player_hands[0] = player_hand;
    game->current_player_hand = 0;
    game->total_player_hands = 1;

    if (dealer_upcard_is_ace(dealer_hand) && !is_blackjack(&player_hand.hand)) {
        draw_hands(game);
        ask_insurance(game);
        return;
    }

    if (player_is_done(game, &player_hand)) {
        dealer_hand->hide_down_card = false;
        pay_hands(game);
        draw_hands(game);
        bet_options(game);
        return;
    }

    draw_hands(game);
    player_get_action(game);
    save_game(game);
}

void get_new_bet(struct Game *game) {
    unsigned tmp;

    clear();
    draw_hands(game);

    printf("  Current Bet: $%u  Enter New Bet: $", (game->current_bet / 100));

    char buffer[32];
    fgets(buffer, 32, stdin);
    tmp = strtoul(buffer, NULL, 0);

    game->current_bet = tmp * 100;
    normalize_bet(game);
    deal_new_hand(game);
}

void get_new_num_decks(struct Game *game) {
    unsigned tmp;

    clear();
    draw_hands(game);

    printf("  Number Of Decks: %u  Enter New Number Of Decks (1-8): ", (game->num_decks));

    char buffer[8];
    fgets(buffer, 8, stdin);
    tmp = strtoul(buffer, NULL, 0);

    if (tmp < 1) tmp = 1;
    if (tmp > 8) tmp = 8;

    game->num_decks = tmp;
    game_options(game);
}

void get_new_deck_type(struct Game *game) {
    clear();
    draw_hands(game);
    printf(" (1) Regular  (2) Aces  (3) Jacks  (4) Aces & Jacks  (5) Sevens  (6) Eights\n");

    while (true) {
        char c = (char) getchar();

        switch (c) {
            case '1':
                new_regular(game);
                break;
            case '2':
                new_aces(game);
                break;
            case '3':
                new_jacks(game);
                break;
            case '4':
                new_aces_jacks(game);
                break;
            case '5':
                new_sevens(game);
                break;
            case '6':
                new_eights(game);
                break;
            default:
                clear();
                draw_hands(game);
                game_options(game);
        }

        draw_hands(game);
        bet_options(game);
        break;
    }
}

void game_options(struct Game *game) {
    clear();
    draw_hands(game);
    printf(" (N) Number of Decks  (T) Deck Type  (B) Back\n");

    while (true) {
        char c = (char) getchar();

        switch (c) {
            case 'n':
                get_new_num_decks(game);
                break;
            case 't':
                get_new_deck_type(game);
                break;
            case 'b':
                clear();
                draw_hands(game);
                bet_options(game);
                break;
            default:
                clear();
                draw_hands(game);
                game_options(game);
        }

        break;
    }
}

void bet_options(struct Game *game) {
    printf(" (D) Deal Hand  (B) Change Bet  (O) Options  (Q) Quit\n");

    while (true) {
        char c = (char) getchar();

        switch (c) {
            case 'd':
                deal_new_hand(game);
                break;
            case 'b':
                get_new_bet(game);
                break;
            case 'o':
                game_options(game);
                break;
            case 'q':
                clear();
                break;
            default:
                clear();
                draw_hands(game);
                bet_options(game);
        }

        break;
    }
}

void process(struct Game *game) {
    if (more_hands_to_play(game)) {
        play_more_hands(game);
        return;
    }

    play_dealer_hand(game);
    draw_hands(game);
    bet_options(game);
}

void play_more_hands(struct Game *game) {
    struct PlayerHand *player_hand = &game->player_hands[++(game->current_player_hand)];
    deal_card(&game->shoe, &player_hand->hand);

    if (player_is_done(game, player_hand)) {
        process(game);
        return;
    }

    draw_hands(game);
    player_get_action(game);
}

void player_hit(struct Game *game) {
    struct PlayerHand *player_hand = &game->player_hands[game->current_player_hand];
    deal_card(&game->shoe, &player_hand->hand);

    if (player_is_done(game, player_hand)) {
        process(game);
        return;
    }

    draw_hands(game);
    player_get_action(game);
}

void player_stand(struct Game *game) {
    struct PlayerHand *player_hand = &game->player_hands[game->current_player_hand];

    player_hand->stood = true;
    player_hand->played = true;

    if (more_hands_to_play(game)) {
        play_more_hands(game);
        return;
    }

    play_dealer_hand(game);
    draw_hands(game);
    bet_options(game);
}

void player_split(struct Game *game) {
    struct PlayerHand new_hand = {.bet=game->current_bet};
    unsigned hand_count = game->total_player_hands;
    struct PlayerHand *this_hand;
    struct PlayerHand *split_hand;
    struct Card card;

    if (!player_can_split(game)) {
        draw_hands(game);
        player_get_action(game);
        return;
    }

    game->player_hands[game->total_player_hands++] = new_hand;

    while (hand_count > game->current_player_hand) {
        game->player_hands[hand_count] = game->player_hands[hand_count - 1];
        --hand_count;
    }

    this_hand = &game->player_hands[game->current_player_hand];
    split_hand = &game->player_hands[game->current_player_hand + 1];

    card = this_hand->hand.cards[1];
    split_hand->hand.cards[0] = card;
    split_hand->hand.num_cards = 1;
    this_hand->hand.num_cards = 1;
    deal_card(&game->shoe, &this_hand->hand);

    if (player_is_done(game, this_hand)) {
        process(game);
        return;
    }

    draw_hands(game);
    player_get_action(game);
}

void player_dbl(struct Game *game) {
    struct PlayerHand *player_hand = &game->player_hands[game->current_player_hand];

    deal_card(&game->shoe, &player_hand->hand);
    player_hand->played = true;
    player_hand->bet *= 2;

    if (player_is_done(game, player_hand)) {
        process(game);
    }
}

void player_get_action(struct Game *game) {
    struct PlayerHand *player_hand = &game->player_hands[game->current_player_hand];
    printf(" ");

    if (player_can_hit(player_hand)) printf("(H) Hit  ");
    if (player_can_stand(player_hand)) printf("(S) Stand  ");
    if (player_can_split(game)) printf("(P) Split  ");
    if (player_can_dbl(game)) printf("(D) Double  ");

    printf("\n");

    while (true) {
        char c = (char) getchar();

        switch (c) {
            case 'h':
                player_hit(game);
                break;
            case 's':
                player_stand(game);
                break;
            case 'p':
                player_split(game);
                break;
            case 'd':
                player_dbl(game);
                break;
            default:
                clear();
                draw_hands(game);
                player_get_action(game);
        }

        break;
    }
}

void buffer_off(struct termios *term) {
    tcgetattr(STDIN_FILENO, term);
    term->c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, term);
}

void buffer_on(struct termios *term) {
    tcgetattr(STDIN_FILENO, term);
    term->c_lflag |= ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, term);
}

void new_regular(struct Game *game) {
    struct Card c;
    game->shoe.num_cards = 0;

    for (unsigned deck = 0; deck < game->num_decks; ++deck) {
        for (unsigned suit = 0; suit < 4; ++suit) {
            c.suit = suit;

            for (unsigned value = 0; value < 13; ++value) {
                c.value = value;
                game->shoe.cards[game->shoe.num_cards++] = c;
            }
        }
    }

    shuffle(&game->shoe);
}

void new_aces(struct Game *game) {
    struct Card c = {.value = 0};
    game->shoe.num_cards = 0;

    for (unsigned deck = 0; deck < game->num_decks * 5; ++deck) {
        for (unsigned suit = 0; suit < 4; ++suit) {
            c.suit = suit;
            game->shoe.cards[game->shoe.num_cards++] = c;
        }
    }
}

void new_aces_jacks(struct Game *game) {
    struct Card c1 = {.value = 0};
    struct Card c2 = {.value = 10};
    game->shoe.num_cards = 0;

    for (unsigned deck = 0; deck < game->num_decks * 4; ++deck) {
        for (unsigned suit = 0; suit < 4; ++suit) {
            c1.suit = suit;
            game->shoe.cards[game->shoe.num_cards++] = c1;

            c2.suit = suit;
            game->shoe.cards[game->shoe.num_cards++] = c2;
        }
    }

    shuffle(&game->shoe);
}

void new_jacks(struct Game *game) {
    struct Card c = {.value = 10};
    game->shoe.num_cards = 0;

    for (unsigned deck = 0; deck < game->num_decks * 5; ++deck) {
        for (unsigned suit = 0; suit < 4; ++suit) {
            c.suit = suit;
            game->shoe.cards[game->shoe.num_cards++] = c;
        }
    }
}

void new_sevens(struct Game *game) {
    struct Card c = {.value = 6};
    game->shoe.num_cards = 0;

    for (unsigned deck = 0; deck < game->num_decks * 5; ++deck) {
        for (unsigned suit = 0; suit < 4; ++suit) {
            c.suit = suit;
            game->shoe.cards[game->shoe.num_cards++] = c;
        }
    }
}

void new_eights(struct Game *game) {
    struct Card c = {.value = 7};
    game->shoe.num_cards = 0;

    for (unsigned deck = 0; deck < game->num_decks * 5; ++deck) {
        for (unsigned suit = 0; suit < 4; ++suit) {
            c.suit = suit;
            game->shoe.cards[game->shoe.num_cards++] = c;
        }
    }
}
