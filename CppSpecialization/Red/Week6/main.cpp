#include "search_server.h"
#include "parse.h"
#include "test_runner.h"
#include "profile.h"

#include <algorithm>
#include <iterator>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <random>
#include <thread>
using namespace std;

void TestFunctionality(
  const vector<string>& docs,
  const vector<string>& queries,
  const vector<string>& expected
) {
  istringstream docs_input(Join('\n', docs));
  istringstream queries_input(Join('\n', queries));

  SearchServer srv;
  srv.UpdateDocumentBase(docs_input);
  ostringstream queries_output;
  srv.AddQueriesStream(queries_input, queries_output);

  const string result = queries_output.str();
  const auto lines = SplitBy(Strip(result), '\n');
  ASSERT_EQUAL(lines.size(), expected.size());
  for (size_t i = 0; i < lines.size(); ++i) {
    ASSERT_EQUAL(lines[i], expected[i]);
  }
}

void TestSerpFormat() {
  const vector<string> docs = {
    "london is the capital of great britain",
    "i am travelling down the river"
  };
  const vector<string> queries = {"london", "the"};
  const vector<string> expected = {
    "london: {docid: 0, hitcount: 1}",
    Join(' ', vector{
      "the:",
      "{docid: 0, hitcount: 1}",
      "{docid: 1, hitcount: 1}"
    })
  };

  TestFunctionality(docs, queries, expected);
}

void TestTop5() {
  const vector<string> docs = {
    "milk a",
    "milk b",
    "milk c",
    "milk d",
    "milk e",
    "milk f",
    "milk g",
    "water a",
    "water b",
    "fire and earth"
  };

  const vector<string> queries = {"milk", "water", "rock"};
  const vector<string> expected = {
    Join(' ', vector{
      "milk:",
      "{docid: 0, hitcount: 1}",
      "{docid: 1, hitcount: 1}",
      "{docid: 2, hitcount: 1}",
      "{docid: 3, hitcount: 1}",
      "{docid: 4, hitcount: 1}"
    }),
    Join(' ', vector{
      "water:",
      "{docid: 7, hitcount: 1}",
      "{docid: 8, hitcount: 1}",
    }),
    "rock:",
  };
  TestFunctionality(docs, queries, expected);
}

void TestHitcount() {
  const vector<string> docs = {
    "the river goes through the entire city there is a house near it",
    "the wall",
    "walle",
    "is is is is",
  };
  const vector<string> queries = {"the", "wall", "all", "is", "the is"};
  const vector<string> expected = {
    Join(' ', vector{
      "the:",
      "{docid: 0, hitcount: 2}",
      "{docid: 1, hitcount: 1}",
    }),
    "wall: {docid: 1, hitcount: 1}",
    "all:",
    Join(' ', vector{
      "is:",
      "{docid: 3, hitcount: 4}",
      "{docid: 0, hitcount: 1}",
    }),
    Join(' ', vector{
      "the is:",
      "{docid: 3, hitcount: 4}",
      "{docid: 0, hitcount: 3}",
      "{docid: 1, hitcount: 1}",
    }),
  };
  TestFunctionality(docs, queries, expected);
}

void TestRanking() {
  const vector<string> docs = {
    "london is the capital of great britain",
    "paris is the capital of france",
    "berlin is the capital of germany",
    "rome is the capital of italy",
    "madrid is the capital of spain",
    "lisboa is the capital of portugal",
    "bern is the capital of switzerland",
    "moscow is the capital of russia",
    "kiev is the capital of ukraine",
    "minsk is the capital of belarus",
    "astana is the capital of kazakhstan",
    "beijing is the capital of china",
    "tokyo is the capital of japan",
    "bangkok is the capital of thailand",
    "welcome to moscow the capital of russia the third rome",
    "amsterdam is the capital of netherlands",
    "helsinki is the capital of finland",
    "oslo is the capital of norway",
    "stockgolm is the capital of sweden",
    "riga is the capital of latvia",
    "tallin is the capital of estonia",
    "warsaw is the capital of poland",
  };

  const vector<string> queries = {"moscow is the capital of russia"};
  const vector<string> expected = {
    Join(' ', vector{
      "moscow is the capital of russia:",
      "{docid: 7, hitcount: 6}",
      "{docid: 14, hitcount: 6}",
      "{docid: 0, hitcount: 4}",
      "{docid: 1, hitcount: 4}",
      "{docid: 2, hitcount: 4}",
    })
  };
  TestFunctionality(docs, queries, expected);
}

void TestBasicSearch() {
  const vector<string> docs = {
    "we are ready to go",
    "come on everybody shake you hands",
    "i love this game",
    "just like exception safety is not about writing try catch everywhere in your code move semantics are not about typing double ampersand everywhere in your code",
    "daddy daddy daddy dad dad dad",
    "tell me the meaning of being lonely",
    "just keep track of it",
    "how hard could it be",
    "it is going to be legen wait for it dary legendary",
    "we dont need no education"
  };

  const vector<string> queries = {
    "we need some help",
    "it",
    "i love this game",
    "tell me why",
    "dislike",
    "about"
  };

  const vector<string> expected = {
    Join(' ', vector{
      "we need some help:",
      "{docid: 9, hitcount: 2}",
      "{docid: 0, hitcount: 1}"
    }),
    Join(' ', vector{
      "it:",
      "{docid: 8, hitcount: 2}",
      "{docid: 6, hitcount: 1}",
      "{docid: 7, hitcount: 1}",
    }),
    "i love this game: {docid: 2, hitcount: 4}",
    "tell me why: {docid: 5, hitcount: 2}",
    "dislike:",
    "about: {docid: 3, hitcount: 2}",
  };
  TestFunctionality(docs, queries, expected);
}

void TestLyrics(){
  const vector<string> docs = {
    "Say, yes they know that you fought yourself another time",
    "Don't they know that you're full of pain already",
    "Yes, they know that you've hurt yourself another time",
    "Decadence isn't easy, is it?",
    "Yes, they know that you've hurt yourself another time",
    "Don't they know that you're full of pain already?",
    "Yes they know that you've hurt yourself another time",
    "Decadence isn't easy",
    "Then you slowly recall all your mind",
    "Why your soul's gone cold and all hope has run dry?",
    "Dead inside",
    "Never enough to forget that you're one of the lonely",
    "Slowly recall all your mind",
    "Say, yes, they know that you've hurt yourself another time",
    "Don't they know that you're full of pain already?",
    "Yes, they know that you've hurt yourself another time",
    "Decadence isn't easy, is it?",
    "Yes, they know that you've hurt yourself another time",
    "Don't they know that you're full of pain already?",
    "Yes, they know that you've hurt yourself another time",
    "Decadence isn't easy",
    "Then you slowly recall all your mind",
    "Why your soul's gone cold and all hope has run dry?",
    "Dead inside",
    "Never enough to forget that you're one of the lonely",
    "Slowly recall all your mind",
    "If I scare you now",
    "Don't run from me",
    "I've been hiding my pain, you see",
    "Said if I scare you now",
    "Don't run from me",
    "I've been hiding my pain, you see",
    "Slowly recall all your mind",
    "Why your soul's gone cold and all hope has run dry?",
    "Dead inside",
    "Never enough to forget that you're one of the lonely",
    "Slowly recall all your mind",
    "Slowly recall all your mind",
    "Say, yes they know that you've hurt yourself another time",
    "Don't they know that you're full of pain already?",
    "Yes, they know that you've hurt yourself another time",
    "Decadence isn't easy, is it",
    "Look, I was gonna go easy on you not to hurt your feelings",
    "But I'm only going to get this one chance (six minutes-, six minutes-)",
    "Something's wrong, I can feel it (six minutes, Slim Shady, you're on!)",
    "Just a feeling I've got, like something's about to happen, but I don't know what",
    "If that means what I think it means, we're in trouble, big trouble",
    "And if he is as bananas as you say, I'm not taking any chances",
    "You are just what the doc ordered",
    "I'm beginnin' to feel like a Rap God, Rap God",
    "All my people from the front to the back nod, back nod",
    "Now, who thinks their arms are long enough to slap box, slap box?",
    "They said I rap like a robot, so call me Rap-bot",
    "But for me to rap like a computer, it must be in my genes",
    "I got a laptop in my back pocket",
    "My pen'll go off when I half-cock it",
    "Got a fat knot from that rap profit",
    "Made a livin' and a killin' off it",
    "Ever since Bill Clinton was still in office",
    "With Monica Lewinsky feelin' on his nutsack",
    "I'm an MC still as honest",
    "But as rude and as indecent as all hell",
    "Syllables, skill-a-holic (kill 'em all with)",
    "This flippity dippity-hippity hip-hop",
    "You don't really wanna get into a pissin' match",
    "With this rappity brat, packin' a MAC in the back of the Ac'",
    "Backpack rap crap, yap-yap, yackety-yack",
    "And at the exact same time, I attempt these lyrical acrobat stunts while I'm practicin' that",
    "I'll still be able to break a motherfuckin' table",
    "Over the back of a couple of faggots and crack it in half",
    "Only realized it was ironic, I was signed to Aftermath after the fact",
    "How could I not blow? All I do is drop F-bombs",
    "Feel my wrath of attack",
    "Rappers are havin' a rough time period, here's a maxi pad",
    "It's actually disastrously bad for the wack",
    "While I'm masterfully constructing this masterpièce",
    "Cause I'm beginnin' to feel like a Rap God, Rap God",
    "All my people from the front to the back nod, back nod",
    "Now, who thinks their arms are long enough to slap box, slap box?",
    "Let me show you maintainin' this shit ain't that hard, that hard",
    "Everybody want the key and the secret to rap immortality like Ι have got",
    "Well, to be truthful the blueprint's",
    "Simply rage and youthful exuberance",
    "Everybody loves to root for a nuisance",
    "Hit the Earth like an asteroid",
    "Did nothing but shoot for the Moon since (pew!)",
    "MCs get taken to school with this music",
    "Cause I use it as a vehicle to bus the rhyme",
    "Now I lead a new school full of students",
    "Me? I'm a product of Rakim",
    "Lakim Shabazz, 2Pac, N.W.A, Cube, hey Doc, Ren",
    "Yella, Eazy, thank you, they got Slim",
    "Inspired enough to one day grow up, blow up and be in a position",
    "To meet Run-D.M.C., induct them",
    "Into the motherfuckin' Rock and Roll Hall of Fame",
    "Even though I'll walk in the church and burst in a ball of flames",
    "Only Hall of Fame I'll be inducted in is the alcohol of fame",
    "On the wall of shame",
    "You fags think it's all a game, 'til I walk a flock of flames",
    "Off a plank and, tell me what in the fuck are you thinkin'?",
    "Little gay-lookin' boy",
    "So gay, I can barely say it with a straight face, lookin' boy (ha-ha!)",
    "You're witnessin' a mass-occur",
    "Like you're watching a church gathering take place, lookin' boy",
    "Oy vey, that boy's gay!, that's all they say, lookin' boy",
    "You get a thumbs up, pat on the back",
    "And a way to go from your label every day, lookin' boy",
    "Hey, lookin' boy! What you say, lookin' boy?",
    "I get a hell yeah from Dre, lookin' boy",
    "I'ma work for everything I have, never asked nobody for shit",
    "Get outta my face, lookin' boy!",
    "Basically, boy, you're never gonna be capable",
    "Of keepin' up with the same pace, lookin' boy, 'cause-",
    "I'm beginnin' to feel like a Rap God, Rap God",
    "All my people from the front to the back nod, back nod",
    "The way I'm racin' around the track, call me NASCAR, NASCAR",
    "Dale Earnhardt of the trailer park, the White Trash God",
    "Kneel before General Zod",
    "This planet's Krypton-, no, Asgard, Asgard",
    "So you'll be Thor and I'll be Odin",
    "You rodent, I'm omnipotent",
    "Let off, then I'm reloadin'",
    "Immediately with these bombs I'm totin'",
    "And I should not be woken",
    "I'm the walkin' dead, but I'm just a talkin' head, a zombie floatin'",
    "But I got your mom deep-throatin'",
    "I'm out my Ramen Noodle",
    "We have nothin' in common, poodle",
    "I'm a Doberman, pinch yourself in the arm and pay homage, pupil",
    "It's me, my honesty's brutal",
    "But it's honestly futile if I don't utilize what I do though",
    "For good at least once in a while",
    "So I wanna make sure somewhere in this chicken scratch I scribble and doodle enough rhymes",
    "To maybe try to help get some people through tough times",
    "But I gotta keep a few punchlines",
    "Just in case 'cause even you unsigned",
    "Rappers are hungry lookin' at me like it's lunchtime",
    "I know there was a time where once I",
    "Was king of the underground",
    "But I still rap like I'm on my Pharoahe Monch grind",
    "So I crunch rhymes, but sometimes when you combine",
    "Appeal with the skin color of mine",
    "You get too big and here they come tryin'",
    "To censor you like that one line",
    "I said on I'm Back from The Mathers LP 1 when I",
    "Tried to say I'll take seven kids from Columbine",
    "Put 'em all in a line, add an AK-47, a revolver and a .9",
    "See if I get away with it now that I ain't as big as I was, but I'm",
    "Morphin' into an immortal, comin' through the portal",
    "You're stuck in a time warp from 2004 though",
    "And I don't know what the fuck that you rhyme for",
    "You're pointless as Rapunzel with fuckin' cornrows",
    "You write normal? Fuck being normal!",
    "And I just bought a new raygun from the future",
    "Just to come and shoot ya, like when Fabolous made Ray J mad",
    "Cause Fab said he looked like a fag at Mayweather's pad",
    "Singin' to a man while he played piano",
    "Man, oh man, that was a 24-7 special on the cable channel",
    "So Ray J went straight to the radio station",
    "The very next day, Hey Fab, I'ma kill you!",
    "Lyrics comin' at you at supersonic speed (J.J. Fad)",
    "Uh, summa-lumma, dooma-lumma, you assumin' I'm a human",
    "What I gotta do to get it through to you I'm superhuman?",
    "Innovative and I'm made of rubber so that anything",
    "You say is ricochetin' off of me, and it'll glue to you and",
    "I'm devastating, more than ever demonstrating",
    "How to give a motherfuckin' audience a feeling like it's levitating",
    "Never fading, and I know the haters are forever waiting",
    "For the day that they can say I fell off, they'll be celebrating",
    "Cause I know the way to get 'em motivated",
    "I make elevating music, you make elevator music",
    "Oh, he's too mainstream",
    "Well, that's what they do when they get jealous, they confuse it",
    "It's not hip-hop, it's pop, 'cause I found a hella way to fuse it",
    "With rock, shock rap with Doc",
    "Throw on Lose Yourself and make 'em lose it",
    "I don't know how to make songs like that",
    "I don't know what words to use",
    "Let me know when it occurs to you",
    "While I'm rippin' any one of these verses that versus you",
    "It's curtains, I'm inadvertently hurtin' you",
    "How many verses I gotta murder to",
    "Prove that if you were half as nice, your songs you could sacrifice virgins too?",
    "Ugh, school flunky, pill junkie",
    "But look at the accolades these skills brung me",
    "Full of myself, but still hungry",
    "I bully myself 'cause I make me do what I put my mind to",
    "And I'm a million leagues above you",
    "Ill when I speak in tongues, but it's still tongue-in-cheek, fuck you",
    "I'm drunk, so, Satan, take the fucking wheel",
    "I'ma sleep in the front seat",
    "Bumpin' Heavy D and the Boyz, still Chunky but Funky",
    "But in my head, there's something I can feel tugging and struggling",
    "Angels fight with devils and here's what they want from me",
    "They're askin' me to eliminate some of the women hate",
    "But if you take into consideration the bitter hatred",
    "I have, then you may be a little patient",
    "And more sympathetic to the situation",
    "And understand the discrimination",
    "But fuck it, life's handin' you lemons? Make lemonade then!",
    "But if I can't batter the women",
    "How the fuck am I supposed to bake them a cake then?",
    "Don't mistake him for Satan; it's a fatal mistake",
    "If you think I need to be overseas and take a vacation",
    "To trip a broad, and make her fall on her face and",
    "Don't be a retard, be a king? Think not",
    "Why be a king when you can be a god?"
  };

  istringstream docs_input(Join('\n', docs));
  SearchServer srv(docs_input);
}

int main() {
  TestRunner tr;
  {
    LOG_DURATION("Common");
    {
      LOG_DURATION("TestLyrics");
      RUN_TEST(tr, TestLyrics);
    }
    {
      LOG_DURATION("TestSerpFormat");
      RUN_TEST(tr, TestSerpFormat);
    }
    {
      LOG_DURATION("TestTop5");
      RUN_TEST(tr, TestTop5);
    }
    {
      LOG_DURATION("TestHitcount");
      RUN_TEST(tr, TestHitcount);
    }
    {
      LOG_DURATION("TestRanking");
      RUN_TEST(tr, TestRanking);
    }
    {
      LOG_DURATION("TestBasicSearch");
      RUN_TEST(tr, TestBasicSearch);
    }
  } 
}
