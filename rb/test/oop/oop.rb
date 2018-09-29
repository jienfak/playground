#!/usr/bin/ruby
#

class Person
	# Testing class.
	
	# Constructor of objects.
	def initialize(name)
		#object field example
		@name = name
	end

	#function examples
	def say(string)
		puts "#{@name}: '#{string}'"
	end

	def action(string)
		puts "*#{@name} #{string}*"
	end
end

person = Person.new('John')
person.say('You suck!')
person.action('kicked you')
