# Knowledge graph
## taxonomic knowledge
Wordnet: class and subclass, but limited  
Wikipedia: catagories contain classes, but not hierarchy  
YAGO: wordnet+wikipedia, connect wikipedia catagories and wordnet class by __random walk__:  
> construct neighborhood around source and target nodes  
> use contextual similarity (glosses etc.) as edge weights  
> compute personalized PR (PPR) with source as start node  
> rank candidate targets by their PPR scores  
KOG(kylin ontology generator): learn classifier for subclass  
extract instance from text: lexico-syntactic patterns  
recursively apply doubly-anchored patterns: W,Y and Z; W,Y belong companies; ==> Z belong companies  
