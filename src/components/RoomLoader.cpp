#include <components/RoomLoader.hpp>
/*
public boolean successLoad(){
        System.out.println(file);
        try {
        // System.out.println(myObj.getAbsolutePath());
            Scanner myReader = new Scanner(file);
            while (myReader.hasNextLine()) {
            	String line = myReader.nextLine();
                String[] data = line.split(" ");
                if (data[0].equalsIgnoreCase("box")) continue; // automaticly added (no need for loading)
                if (line.length()<3) continue; // invalid
                if (!Character.isDigit(line.charAt(0))) {
                	additionalCommands += line+"\n";
                	continue;
                }
                // parse
                int[] obj = new int[Drawable.MAX_COMPONENTS];
                int index = 0;
                for (String comp : data) {
                	if (comp.length()<1) continue;
                	obj[index++] = Integer.parseInt(comp);
                }
                l.add(obj);
            }
            myReader.close();
            return true;
        } catch (FileNotFoundException e) {
            System.out.println("An error occurred.");
        }
        return false;
    }
        */

#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>
#include <iostream>
#include <components/Room.hpp>

namespace room_loader {
    std::vector<Drawable::DrawableData> objects;
} // namespace room_loader


int __lvl_loader_load(const std::string& filepath) {
    std::ifstream file(filepath);

    room_loader::objects.clear();
    
    std::string line;
    while (std::getline(file, line)) {
        if (!std::isdigit(line[0])){
            std::cout << line << std::endl;
            continue;
        }
        std::istringstream _l(line);
        Drawable::DrawableData data = DRAWABLE_DEFAULT_DATA; int index=0;
        std::string token;
        while (std::getline(_l, token, ' ')) {
            data[index++] = std::stoi(token);
            if (index>=Drawable::COMPONENT_COUNT) break;
        }
        room_loader::objects.push_back(data);
    }

    file.close();

    return 0;
}



int room_loader::load(unsigned int roomID) {
    std::string filepath("/Users/luka/eclipse-workspace/Pastir-editor/");
    filepath += std::to_string(roomID);
    filepath += ".txt";
    if (!std::filesystem::exists(filepath)) {
        fprintf(stderr, "<LVLLOADER> Room %u doesn't exists. path=%s\n", roomID, filepath.c_str());
        return -1;
    }
    printf("<LVLLOADER> Loading room %u path=%s\n", roomID, filepath.c_str());
    return __lvl_loader_load(filepath);
}



void room_loader::swapObjects(Room& room) {
    objects.swap(room.objects);
}