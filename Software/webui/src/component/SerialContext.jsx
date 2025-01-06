import React, { createContext, useRef, useState } from "react";

export const SerialContext = createContext();

export const SerialProvider = ({ children }) => {
    const [port, setPort] = useState(null);
    const [output, setOutput] = useState("");
    const [receivedData, setReceivedData] = useState(""); // Dữ liệu nhận được từ Serial
    const portRef=useRef(null);
  const connectToSerial = async () => {
    if ("serial" in navigator) {
      try {
        const selectedPort = await navigator.serial.requestPort();
        await selectedPort.open({ baudRate: 115200 });
        portRef.current=selectedPort;
        alert("Connected to Foot Keyboard");
        // Gửi tin nhắn ngay khi kết nối thành công
        await sendData("ALL=",selectedPort);

        // Đọc dữ liệu phản hồi sau khi gửi tin nhắn
        await readData(selectedPort);
      } catch (error) {
        console.error("Error connecting to serial port:", error);
        setOutput("Failed to connect to serial port.");
      }
    } else {
      setOutput("Web Serial API is not supported in your browser.");
    }
  };
  const sendData = async (message,port) => {
    if (true) {
      const encoder = new TextEncoderStream();
      const writableStreamClosed = encoder.readable.pipeTo(portRef.writable);
      const writer = encoder.writable.getWriter();
      await writer.write(message + "\n");
      writer.releaseLock();
    } else {
      console.error("No serial connection available.");
    }
  };

  const readData = async (port) => {
    if (port) {
      const decoder = new TextDecoderStream();
      const readableStreamClosed = port.readable.pipeTo(decoder.writable);
      const reader = decoder.readable.getReader();
      let data="";
      try {
        const { value, done } = await reader.read();
        data+=value;  
        alert(data);
         // Lưu dữ liệu nhận được
      } catch (error) {
        console.error("Error reading from serial port:", error);
      } finally {
        reader.releaseLock();
        
        setReceivedData(data);
      }
    } else {
      console.error("No serial connection available.");
    }
  };
  
  return (
    <SerialContext.Provider
      value={{
        connectToSerial,
        sendData,
        receivedData,
        output,
        port, 
        setPort,
      }}
    >
      {children}
    </SerialContext.Provider>
  );
};
