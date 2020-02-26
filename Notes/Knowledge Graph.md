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

## factual knowledge
relations between entities  
#### Regex based
Information extraction: Source-centric and Yield-centric(focus, more precision)  
#### Pattern based
map pairs to patterns  
PMI(e1,e2)=log freq(e1,e2)/(freq(e1)* freq(e2))  
* use negative seeds to increase precision:  
compute conf as occurrence of p with positive seeds / occur of p with pos seeds and neg seeds  
* generalized patterns increase recall  
* Deep parsing  
#### consistency reasoning
transform IE to logic rules:
* transform corpus to surface statements
* add possible meanings
* add pattern deduction rules
* add semantic constraints/ remove inconsistencies    
pose a weighted max satisify problem  
#### probabilistic method
markov logic generalizes MaxSat reasoning  
MLN( markov logic netowrk ), large-scale: statsnowball  
#### web table method
map header with yago classes, value with entities.  
statistics yield semantics  
__*conclusion*__: _bootstrapping_ works well for recall, consistency reasoning is crucial for high precision,   
## emerging knowledge
new entities and relations  
frequent sequence mining, map-reduce  
pipeline: text pre-processing ==> n-gram mining ==> pattern lifting ==> taxonomy reconstruction
## temporal knowledge
validity times of facts, add time factor  
relation, time(from to)  
combine linguistics, statistics, logical reasoning. order relation.  
## contextual knowledge
#### named entity recognition and disambiguation  
* contextual similarity
* coherence of entity pairs
    * semantic relationship
    * shared types
    * overlap of wikipedia links
    * overlap of entity-specific keyphrases
#### coherence-based method
1. prob factor graph
    * build mention-entity graph or joint-inference factor graph from knowledge and statistics in KB
    * compute high-likelihood mapping or dense subgraph such that each m is connected to exactly one e or atmost one e
2. dense subgraph 
3. conherence graph algorithm
4. random walks algorithm
#### entities in structured data/entity resolution
similarity of entities depends on similarity of neighborhoods  
## commonsense knowledge
* crowdsourcing (network flow)
* pattern-based
* semantic types (compute ranges, domains, assertions)
* pattern indicate to inference:
    * standard confidence: #cases where rule holds/#all cases
    * PCA(partial completeness assumption) conf: #cases where rule holds/(#rule holds + rule produces wrong prediction)
    * AMIE: rule mining on KB
* advanced rules(more reasoning, handle negations, cope with reporting bias)
* knowledge from image and photos
## Knowledge bases
entities, relations, time, space
* scalable algor.
* distributed platforms
* discovering data sources
* tapping unstructured data
* connecting structured and unstructured data sources
* making sense of heterogeneous, dirty or uncertain data
