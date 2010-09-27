from reverend.thomas import Bayes
guesser = Bayes()
guesser.train('french', 'le la les du un une je il elle de en')
guesser.train('german', 'der die das ein eine')
guesser.train('spanish', 'el uno una las de la en')
guesser.train('english', 'the it she he they them are were to')
print guesser.guess('they went to el cantina')
print guesser.guess('they were flying planes')
guesser.train('english', 'the rain in spain falls mainly on the plain')
guesser.save('my_guesser.bay')
