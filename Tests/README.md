# Ft_containers testeur
https://profile.intra.42.fr/users/llaurent

* <b>Synopsis</b> : Ce projet est une introduction à la STL et aux containers

* <b>But du testeur</b> : Le but est de tester vos containers, en vous permettant de modifier les tests très rapidement et de lancer uniquement ceux que vous souhaitez

<hr>

* <b>Installation</b> : allez dans le dossier de votre ft_containers, git clonez le testeur. Il vous suffira d'aller dans le main, mettre les includes correspondant à vos fichiers et de lancer un `make test` pour effectuer les tests présents dans le main

* <b>Notes importantes</b> :
   - Tous les tests unitaires sont stockés dans le dosier "unit_tests" depuis la racine
   - Pour lancer un test spécifique depuis le main, vous devez déclarer une `std::list`, y ajouter le nom des tests correspondants (tous les noms de tests se trouvent dans le dossier `handlers`) et passer cette `std::list` dans les fonctions `exec_x`.
   - Par défaut, les fonctions `exec_x` lancent tous les tests qui se trouvent dans le handler correspondant au test.