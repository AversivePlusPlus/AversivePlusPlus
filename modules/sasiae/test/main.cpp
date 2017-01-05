/*
    Aversive++                                                           
    Copyright (C) 2014 Eirbot                                            
                                                                         
    This program is free software: you can redistribute it and/or modify 
    it under the terms of the GNU General Public License as published by 
    the Free Software Foundation, either version 3 of the License, or    
    (at your option) any later version.                                  
                                                                         
    This program is distributed in the hope that it will be useful,      
    but WITHOUT ANY WARRANTY; without even the implied warranty of       
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        
    GNU General Public License for more details.                         
                                                                         
    You should have received a copy of the GNU General Public License    
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stream/sasiae/stream.hpp>
#include <device/sasiae/encoder.hpp>
#include <device/sasiae/motor.hpp>
#include <sasiae/asynchronous_updater.hpp>

Aversive::Device::SASIAE::Motor m("motor");

class MyAsync : public Aversive::Device::Asynchronous<MyAsync> {
public:
  void update(void) {
    m.setValue(10);
  }
};

int main(int, char**) {
  MyAsync as;

  SASIAE::AsynchronousUpdaterConstructor::instance()
      .build(as, 10)
      .start();

  while(SASIAE::Aversive::sync()) {
    }

  return 0;
}
